#include <sstream>
#include <iomanip>
#include <vector>
#include "graphics.h"
#include "map.h"
#include "color.h"
#include "entity.h"
#include "job.h"
#include "entity_style.h"
#include "globals.h"
#include "entity_manager.h"
#include "utility.h"
#include "pathfinding.h"
#include <algorithm>

Graphics::Graphics()
{
	verticalLine.setSize(Vec2f(LINE_WIDTH, map.size.y + LINE_WIDTH));//updateShapeSize instead
	verticalLine.setFillColor(colors.transparentGrey);

	horizontalLine.setSize(Vec2f(map.size.x + LINE_WIDTH, LINE_WIDTH));
	horizontalLine.setFillColor(colors.transparentGrey);

	selectionShape.setFillColor(colors.transparent);
	selectionShape.setOutlineColor(colors.green);
	selectionShape.setOutlineThickness(-1);

	RectangleShape grassRect;
	RectangleShape waterRect;

	waterRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	waterRect.setFillColor(colors.darkBlue);
	terrainShapes.push_back(waterRect);

	grassRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	grassRect.setFillColor(colors.darkGreen);
	terrainShapes.push_back(grassRect);

	Texture grassTexture;
	Texture waterTexture;

	terrainTextures.push_back(waterTexture);
	terrainTextures.push_back(grassTexture);

	if (!terrainTextures.at(0).loadFromFile("data/water.png")) {
		throw std::logic_error("could not load texture");
	}
	if (!terrainTextures.at(1).loadFromFile("data/grass.png")) {
		throw std::logic_error("could not load texture");
	}

	Sprite grassSprite;
	Sprite waterSprite;

	waterSprite.setTexture(terrainTextures.at(0));
	grassSprite.setTexture(terrainTextures.at(1));

	terrainSprites.push_back(waterSprite);
	terrainSprites.push_back(grassSprite);

	pathDebugShape.setRadius(PATH_DEBUG_SIZE / 2); //TODO
}

void Graphics::draw() {
	renderWindow.clear();
	drawWorld();
	drawHUD();
	renderWindow.display();
}

void Graphics::drawWorld() {
	renderWindow.setView(mapView);
	drawTerrain();
	if (showGrid)
		drawGrid();
	drawEntities();
	if (selectionRectActive)
		drawSelectionRect();
}

void Graphics::drawTerrain() {
	for (int x = 0; x < map.terrainGrid.size(); ++x) {
		for (int y = 0; y < map.terrainGrid[x].size(); ++y) {
			terrainShapes.at(map.terrainGrid[x][y]).
				setPosition(Vec2f(TILE_SIZE * float(x), TILE_SIZE * (float)y));
			renderWindow.draw(terrainShapes.at(map.terrainGrid[x][y]));
			/*terrainSprites.at(map.terrainGrid[x][y]).
				setPosition(Vec2f(TILE_SIZE * float(x), TILE_SIZE * (float)y));
			renderWindow.draw(terrainSprites.at(map.terrainGrid[x][y]));*/
		}
	}
}

void Graphics::drawGrid() {
	for (int i = 0; i < map.tileCount.x + 1; ++i) {
		verticalLine.setPosition(Vec2f(TILE_SIZE * i - LINE_WIDTH_HALF, -LINE_WIDTH_HALF));
		renderWindow.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; ++i) {
		horizontalLine.setPosition(Vec2f(-LINE_WIDTH_HALF, TILE_SIZE * i - LINE_WIDTH_HALF));
		renderWindow.draw(horizontalLine);
	}
}

void Graphics::drawEntities() {
	if (showPaths) {
		for (auto& it : em.all_entities) {
			Entity* entity_ptr = it.second;
			if (entity_ptr->isGarrisoned == false) {
				if (entity_ptr->jobQueue.size() > 0) {
					Job* job_ptr = entity_ptr->jobQueue.at(0);
					if (job_ptr->getPath() != nullptr) {
						drawSearchPath(*job_ptr->getPath(), colors.teal);
					}
				}
			}
		}
	}
	for (auto& it : em.all_entities) {
		if (it.second->isGarrisoned == false) {
			Vec2f graphicalPos = getTopLeft(it.second->pos, it.second->style.size);
			Shape* shape = it.second->style.getShape(graphicalPos, false);
			renderWindow.draw(*shape);
		}
	}
	for (auto entity : selectedEntities) {
			Vec2f graphicalPos = getTopLeft(entity->pos, entity->style.size);
			Shape* outlineShape = entity->style.getOutlineShape(graphicalPos);
			renderWindow.draw(*outlineShape);
	}
	if (placementEntityStyle != nullptr) {
		if (map.isWithinBounds(mouseTile)) {
			Vec2f snappedPos = tileToWorld(worldToTile(mouseWorldPos));
			Vec2f graphicalPos = getTopLeft(snappedPos, placementEntityStyle->size);
			bool tintRed = !placementEntityStyle->tileIsPathable(mouseTile);
			Shape* placementShape = placementEntityStyle->getShape(graphicalPos, tintRed);
			renderWindow.draw(*placementShape);
		}
	}
}

void Graphics::drawSelectionRect() {
	float rectLeft = std::min(selectionStartPos.x, mouseWorldPos.x);
	float rectRight = std::max(selectionStartPos.x, mouseWorldPos.x);
	float rectTop = std::min(selectionStartPos.y, mouseWorldPos.y);
	float rectBot = std::max(selectionStartPos.y, mouseWorldPos.y);
	selectionShape.setPosition(Vec2f(rectLeft, rectTop));
	selectionShape.setSize(Vec2f(rectRight - rectLeft, rectBot - rectTop));
	renderWindow.draw(selectionShape);
}

void Graphics::drawHUD() {
	renderWindow.setView(renderWindow.getDefaultView());
	updateText();
	renderWindow.draw(ui.hud);
}

void Graphics::updateText() {
	ui.targetFpsPanel.setString((oss() << "TargetFPS: " << targetFPS).str());
	ui.actualFpsPanel.setString((oss() << "FPS: " << (int)(actualFPS + 0.5)).str());
	ui.unitCountPanel.setString((oss() << "Units: " << em.all_units.size()).str());
	ui.houseCountPanel.setString((oss() << "Houses: " << em.all_houses.size()).str());
	ui.timePanel.setString((oss() << "Time: " << seconds).str());
	ui.zoomPanel.setString((oss() << "Zoom: " << zoom).str());

	oss entityStringStream;
	entityStringStream << "Entities Selected: " << selectedEntities.size() << std::endl << std::endl;
	if (selectedEntities.size() > 0)
	{
		auto it = selectedEntities.begin();
		(*it)->getSelectionText(entityStringStream);
		ui.selectionPanel.setString(entityStringStream.str());
	}
	ui.selectionPanel.setString(entityStringStream.str());
}

void Graphics::drawAStar(const Vec2i* current, std::list<Vec2i>* path) {
	renderWindow.clear();
	drawWorld();

	drawClosed(aStar.closed, colors.white);
	drawAStarOpen(aStar.open, colors.red);
	if (path)
		drawSearchPath(*path, colors.teal);

	drawSearchTile(aStar.start, colors.white);
	drawSearchTile(aStar.end, colors.yellow);
	if (current)
		drawSearchTile(*current, colors.orange);

	drawHUD();
	renderWindow.display();
}

void Graphics::drawBreadthFirst(const Vec2i* end, const Vec2i* current, std::list<Vec2i>* path) {
	renderWindow.clear();
	drawWorld();

	drawClosed(breadthFirst.closed, colors.white);
	drawBreadthFirstOpen(breadthFirst.open, colors.red);
	if (path)
		drawSearchPath(*path, colors.teal);
	drawSearchTile(breadthFirst.start, colors.white);
	if (end)
		drawSearchTile(*end, colors.yellow);
	if (current)
		drawSearchTile(*current, colors.orange);

	drawHUD();
	renderWindow.display();
}

void Graphics::drawSearchPath(const std::list<Vec2i>& path, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (auto i = path.begin(); i != path.end(); i++) {
		drawSearchTile((*i), color);
	}
}

void Graphics::drawSearchTile(const Vec2i tile, const Color& color) {
	pathDebugShape.setFillColor(color);
	pathDebugShape.setPosition(getTopLeft(tileToWorld(tile), PATH_DEBUG_SIZE));
	renderWindow.draw(pathDebugShape);
}

void Graphics::drawAStarOpen(const std::vector<AStarOpenTuple>& open, const Color& color) {
	for (auto i = open.begin(); i != open.end(); i++) {
		drawSearchTile(std::get<2>(*i), color);
	}
}

void Graphics::drawBreadthFirstOpen(const std::vector<BreadthFirstOpenTuple>& open, const Color& color) {
	for (auto i = open.begin(); i != open.end(); i++) {
		drawSearchTile(std::get<1>(*i), color);
	}
}

void Graphics::drawClosed(const std::set<Vec2i, CompareVec2i>& closed, const Color& color) {
	for (auto i = closed.begin(); i != closed.end(); i++) {
		drawSearchTile((*i), color);
	}
}

void Graphics::updateShapeSizes() {
	verticalLine.setSize(Vec2f(LINE_WIDTH, map.size.y + LINE_WIDTH));
	horizontalLine.setSize(Vec2f(map.size.x + LINE_WIDTH, LINE_WIDTH));
	terrainShapes.at(0).setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	terrainShapes.at(1).setSize(Vec2f(TILE_SIZE, TILE_SIZE));
}
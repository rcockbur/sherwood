#include <assert.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include "graphics.h"
#include "map.h"
#include "color.h"
#include "entity.h"
#include "entity_type.h"
#include "globals.h"
#include "entity_manager.h"
#include "utility.h"


Graphics::Graphics()
{
	verticalLine.setSize(Vec2f(LINE_WIDTH, map.size.y + LINE_WIDTH));
	verticalLine.setFillColor(colors.lightGrey);

	horizontalLine.setSize(Vec2f(map.size.x + LINE_WIDTH, LINE_WIDTH));
	horizontalLine.setFillColor(colors.lightGrey);

	RectangleShape grassRect;
	RectangleShape waterRect;

	waterRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	waterRect.setFillColor(colors.darkBlue);
	terrainShapes.push_back(waterRect);

	grassRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	grassRect.setFillColor(colors.darkGreen);
	terrainShapes.push_back(grassRect);

	pathDebugShape.setRadius(PATH_DEBUG_SIZE / 2);
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
}

void Graphics::drawTerrain() {
	for (int x = 0; x < map.terrainGrid.size(); ++x) {
		for (int y = 0; y < map.terrainGrid[x].size(); ++y) {
			terrainShapes.at(map.terrainGrid[x][y]).
				setPosition(Vec2f(TILE_SIZE * float(x), TILE_SIZE * (float)y));
			renderWindow.draw(terrainShapes.at(map.terrainGrid[x][y]));
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
	for (auto& entity : em.entities) {
		Vec2f graphicalPos = getTopLeft(entity->pos, entity->entityType().size);
		Shape* shape = entity->entityType().getShape(graphicalPos);
		renderWindow.draw(*shape);
	}
	if (selectedEntity != nullptr) {
		Vec2f graphicalPos = getTopLeft(selectedEntity->pos, selectedEntity->entityType().size);
		Shape* outlineShape = selectedEntity->entityType().getOutlineShape(graphicalPos);
		renderWindow.draw(*outlineShape);
	}
	if (placementBuildingType != nullptr) {
		if (mouseWorldPos != Vec2f(-1, -1)) {
			Vec2f snappedPos = tileToWorld(worldToTile(mouseWorldPos));
			Vec2f graphicalPos = getTopLeft(snappedPos, placementBuildingType->size);
			Shape* placementShape = placementBuildingType->getShape(graphicalPos);
			renderWindow.draw(*placementShape);
		}
	}
}

void Graphics::drawHUD() {
	renderWindow.setView(renderWindow.getDefaultView());
	updateText();
	renderWindow.draw(ui.hud);
}

void Graphics::updateText() {
	ui.targetFpsPanel.setString((oss() << "TargetFPS: " << targetFPS).str());
	ui.actualFpsPanel.setString((oss() << "FPS: " << (int)actualFPS).str());
	ui.unitCountPanel.setString((oss() << "Units: " << em.unitMap.size()).str());
	ui.timePanel.setString((oss() << "Time: " << seconds).str());

	if (selectedEntity != nullptr) {
		oss entityStringStream;
		selectedEntity->getSelectionText(entityStringStream);
		ui.selectionPanel.setString(entityStringStream.str());
	}
	else {
		ui.selectionPanel.setString("");
	}
}

void Graphics::drawAStar(const std::vector<AStarOpenTuple>& open, const std::set<Vec2i, CompareVec2i>& closed,
	const Vec2i& s, const Vec2i& e, const Vec2i* current, std::list<Vec2i>* path) {
	renderWindow.clear();
	drawWorld();

	
	drawClosed(closed, colors.white);
	drawAStarOpen(open, colors.red);
	if (path != nullptr)
		drawSearchPath(*path, colors.teal);

	drawSearchTile(s, colors.white);
	drawSearchTile(e, colors.yellow);
	if (current)
		drawSearchTile(*current, colors.orange);
	drawHUD();
	renderWindow.display();
}

void Graphics::drawBreadthFirst(const std::list<node2>& open, const std::list<node2>& closed,
	const Vec2i& start, const Vec2i& end, std::list<Vec2i>* path) {

	renderWindow.clear();
	drawWorld();

	drawSearchNodes2(open, colors.red);
	drawSearchNodes2(closed, colors.white);
	if (path != nullptr)
		drawSearchPath(*path, colors.teal);

	drawSearchTile(start, colors.white);
	if (end.x != -1)
		drawSearchTile(end, colors.yellow);

	drawHUD();
	renderWindow.display();
}

void Graphics::drawBreadthFirstNew(const std::vector<BreadthFirstOpenTuple>& open, const std::set<Vec2i, CompareVec2i>& closed,
	const Vec2i& s, const Vec2i* e, const Vec2i* current, std::list<Vec2i>* path) {
	renderWindow.clear();
	drawWorld();


	drawClosed(closed, colors.white);
	drawBreadthFirstOpen(open, colors.red);
	if (path != nullptr)
		drawSearchPath(*path, colors.teal);

	drawSearchTile(s, colors.white);
	if (e)
		drawSearchTile(*e, colors.yellow);
	if (current)
		drawSearchTile(*current, colors.orange);
	drawHUD();
	renderWindow.display();
}

void Graphics::drawSearchNodes(const std::list<node>& nodes, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		drawDebugTile((*i).tile);
	}
}

void Graphics::drawSearchNodes2(const std::list<node2>& nodes, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		drawDebugTile((*i).tile);
	}
}

void Graphics::drawSearchPath(const std::list<Vec2i>& path, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (auto i = path.begin(); i != path.end(); i++) {
		drawDebugTile((*i));
	}
}

void Graphics::drawSearchTile(const Vec2i tile, const Color& color) {
	pathDebugShape.setFillColor(color);
	drawDebugTile(tile);
}

void Graphics::drawDebugTile(const Vec2i tile) {
	pathDebugShape.setPosition(getTopLeft(tileToWorld(tile), PATH_DEBUG_SIZE));
	renderWindow.draw(pathDebugShape);
}



void Graphics::drawAStarOpen(const std::vector<AStarOpenTuple>& open, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (auto i = open.begin(); i != open.end(); i++) {
		drawDebugTile(std::get<2>(*i));
	}
}

void Graphics::drawBreadthFirstOpen(const std::vector<BreadthFirstOpenTuple>& open, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (auto i = open.begin(); i != open.end(); i++) {
		drawDebugTile(std::get<1>(*i));
	}
}

void Graphics::drawClosed(const std::set<Vec2i, CompareVec2i>& closed, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (auto i = closed.begin(); i != closed.end(); i++) {
		drawDebugTile((*i));
	}
}
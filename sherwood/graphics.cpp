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

	sf::RectangleShape grassRect;
	sf::RectangleShape waterRect;

	waterRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	waterRect.setFillColor(colors.blue);
	terrainShapes.push_back(waterRect);

	grassRect.setSize(Vec2f(TILE_SIZE, TILE_SIZE));
	grassRect.setFillColor(colors.green);
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
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(Vec2f(TILE_SIZE * i - LINE_WIDTH_HALF, -LINE_WIDTH_HALF));
		renderWindow.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(Vec2f(-LINE_WIDTH_HALF, TILE_SIZE * i - LINE_WIDTH_HALF));
		renderWindow.draw(horizontalLine);
	}
}

void Graphics::drawEntities() {
	for (auto& entity : em.entities) {
		Vec2f graphicalPos = entity->position - Vec2f(entity->type.size / 2, entity->type.size / 2);
		sf::Shape* shape = entity->type.getShape(graphicalPos);
		renderWindow.draw(*shape);
		if (entity->isSelected) {
			sf::Shape* outlineShape = entity->type.getOutlineShape(graphicalPos);
			renderWindow.draw(*outlineShape);
		}
	}
	if (placementBuildingType != nullptr) {
		if (mouseWorldPos != Vec2f(-1, -1)) {
			Vec2f snappedPos = tileToWorld(worldToTile(mouseWorldPos));
			Vec2f graphicalPos = snappedPos - Vec2f(placementBuildingType->size / 2, placementBuildingType->size / 2);

			sf::Shape* placementShape = placementBuildingType->getShape(graphicalPos);
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
}

void Graphics::drawSearchDebug(const std::list<node>& open, const std::list<node>& closed, 
	const Vec2i& start, const Vec2i& end, std::list<Vec2i> * path) {

	renderWindow.clear();
	drawWorld();
	
	drawSearchNodes(open, colors.red);
	drawSearchNodes(closed, colors.purple);
	if (path != nullptr)
		drawSearchPath(*path, colors.teal);

	drawSearchTile(start, colors.white);
	drawSearchTile(end, colors.yellow);

	drawHUD();
	renderWindow.display();
}

void Graphics::drawSearchNodes(const std::list<node>& nodes, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (std::list<node>::const_iterator i = nodes.begin(); i != nodes.end(); i++) {
		pathDebugShape.setPosition(tileToWorld((*i).tile) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
		renderWindow.draw(pathDebugShape);

	}
}
void Graphics::drawSearchPath(const std::list<Vec2i>& path, const Color& color) {
	pathDebugShape.setFillColor(color);
	for (std::list<Vec2i>::const_iterator i = path.begin(); i != path.end(); i++) {
		pathDebugShape.setPosition(tileToWorld((*i)) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
		renderWindow.draw(pathDebugShape);
	}
}

void Graphics::drawSearchTile(const Vec2i& tile, const Color& color) {
	pathDebugShape.setFillColor(color);
	pathDebugShape.setPosition(tileToWorld(tile) - Vec2f(PATH_DEBUG_SIZE / 2, PATH_DEBUG_SIZE / 2));
	renderWindow.draw(pathDebugShape);
}
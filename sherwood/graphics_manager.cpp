#include <assert.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include "graphics_manager.h"
#include "map.h"
#include "color.h"
#include "entity.h"
#include "window_manager.h"
#include "globals.h"
#include "entity_manager.h"

GraphicsManager::GraphicsManager() 
{
	viewportShape.setSize(VIEWPORT_SIZE);
	viewportShape.setPosition(VIEWPORT_OFFSET);
	viewportShape.setOutlineColor(color.red);
	viewportShape.setOutlineThickness(1);
	viewportShape.setFillColor(color.transparent);

	verticalLine.setSize(Vec2f(LINE_WIDTH, wm.gridSize.y + LINE_WIDTH));
	verticalLine.setFillColor(color.grey);

	horizontalLine.setSize(Vec2f(wm.gridSize.x + LINE_WIDTH, LINE_WIDTH));
	horizontalLine.setFillColor(color.grey);

	sf::RectangleShape grassRect;
	sf::RectangleShape waterRect;

	grassRect.setSize(TILE_SIZE);
	grassRect.setFillColor(color.darkGreen);
	terrainShapes.push_back(grassRect);

	waterRect.setSize(TILE_SIZE);
	waterRect.setFillColor(color.blue);
	terrainShapes.push_back(waterRect);

	entityShape.setSize(ENTITY_SIZE);
	entityShape.setFillColor(color.white);

	selectionShape.setSize(ENTITY_SIZE);
	selectionShape.setOutlineThickness(LINE_WIDTH);
	selectionShape.setOutlineColor(color.yellow);
	selectionShape.setFillColor(color.transparent);

	//pathDebugShape.setSize(ENTITY_SIZE);
	pathDebugShape.setSize(PATH_DEBUG_SIZE);

	if (!arial.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");
	initText(fpsText, Vec2f(WINDOW_PADDING_LEFT, WINDOW_PADDING_TOP));
	initText(selectionText, RIGHT_PANEL_OFFSET);
}

void GraphicsManager::draw() {
	wm.window.clear();
	drawWorld();
	drawHUD();
	wm.window.display();
}

void GraphicsManager::drawWorld() {
	wm.window.setView(wm.mapView);
	drawTerrain();
	if (showGrid)
		drawGrid();
	drawEntities();
}

void GraphicsManager::drawHUD() {
	wm.window.setView(wm.window.getDefaultView());
	drawViewportOutline();
	drawText();
}

void GraphicsManager::drawTerrain() {
	for (int x = 0; x < map.terrainGrid.size(); ++x) {
		for (int y = 0; y < map.terrainGrid[x].size(); ++y) {
			terrainShapes.at(map.terrainGrid[x][y]).
				setPosition(Vec2f(TILE_SIZE.x * float(x), TILE_SIZE.y * (float)y));
			wm.window.draw(terrainShapes.at(map.terrainGrid[x][y]));
		}
	}
}

void GraphicsManager::drawEntities() {
	for (auto& entity : em.entities) {
		Vec2f graphicalPosition = entity->position - Vec2f(ENTITY_SIZE.x / 2, ENTITY_SIZE.y / 2);
		entityShape.setPosition(graphicalPosition);
		entityShape.setFillColor(entity->color);
		wm.window.draw(entityShape);
		if (entity->isSelected) {
			selectionShape.setPosition(graphicalPosition);
			wm.window.draw(selectionShape);
		}
	}	
}

void GraphicsManager::drawGrid() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(Vec2f(TILE_SIZE.x * i - LINE_WIDTH_HALF, -LINE_WIDTH_HALF));
		wm.window.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(Vec2f(-LINE_WIDTH_HALF, TILE_SIZE.y * i - LINE_WIDTH_HALF));
		wm.window.draw(horizontalLine);
	}
}

void GraphicsManager::drawText() {
	drawTextFPS();
	drawTextSelection();
}

void GraphicsManager::drawTextFPS() {
	std::ostringstream s;
	s << "Target FPS: " << wm.targetFPS;
	//s << "   Actual FPS: " << std::setprecision(3) << wm.actualFPS;
	s << "   Actual FPS: " << (int)wm.actualFPS;
	fpsText.setString(s.str());
	wm.window.draw(fpsText);
}

void GraphicsManager::drawTextSelection() {
	if (selectedEntity != nullptr) {
		std::ostringstream s;
		s << "Entity\n";
		s << "ID: " << selectedEntity->id << "\n";
		s << "Tile: " << selectedEntity->tile << "\n";
		s << "Pos: " << (Vec2i)(selectedEntity->position) << "\n";
		selectionText.setString(s.str());
		wm.window.draw(selectionText);
	}
}

void GraphicsManager::drawViewportOutline() {
	wm.window.draw(viewportShape);
}

void GraphicsManager::drawPathDebug(const std::list<node>& open, const std::list<node>& closed, 
	const Vec2i& s, const Vec2i& e, std::list<Vec2i> * path) {
	wm.window.clear();
	drawWorld();
	
	pathDebugShape.setFillColor(color.red);
	for (std::list<node>::const_iterator i = open.begin(); i != open.end(); i++) {
		if ((*i).tile != s) {
			pathDebugShape.setPosition(wm.tileToWorld((*i).tile) - Vec2f(PATH_DEBUG_SIZE.x / 2, PATH_DEBUG_SIZE.y / 2));
			wm.window.draw(pathDebugShape);
		}
		
	}
	pathDebugShape.setFillColor(color.purple);
	for (std::list<node>::const_iterator i = closed.begin(); i != closed.end(); i++) {
		if ((*i).tile != s) {
			pathDebugShape.setPosition(wm.tileToWorld((*i).tile) - Vec2f(PATH_DEBUG_SIZE.x / 2, PATH_DEBUG_SIZE.y / 2));
			wm.window.draw(pathDebugShape);
		}	
	}
	if (path != nullptr) {
		pathDebugShape.setFillColor(color.teal);
		for (std::list<Vec2i>::iterator i = (*path).begin(); i != (*path).end(); i++) {
			pathDebugShape.setPosition(wm.tileToWorld((*i)) - Vec2f(PATH_DEBUG_SIZE.x / 2, PATH_DEBUG_SIZE.y / 2));
			wm.window.draw(pathDebugShape);
		}
	}
	

	pathDebugShape.setFillColor(color.white);
	pathDebugShape.setPosition(wm.tileToWorld(s) - Vec2f(PATH_DEBUG_SIZE.x / 2, PATH_DEBUG_SIZE.y / 2));
	wm.window.draw(pathDebugShape);

	pathDebugShape.setFillColor(color.yellow);
	pathDebugShape.setPosition(wm.tileToWorld(e) - Vec2f(PATH_DEBUG_SIZE.x / 2, PATH_DEBUG_SIZE.y / 2));
	wm.window.draw(pathDebugShape);

	drawHUD();
	wm.window.display();
}

void GraphicsManager::initText(sf::Text& text, const Vec2f& position) {
	text.setFont(arial);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);
	text.setPosition(position);
}
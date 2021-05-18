#include <assert.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include "graphics_manager.h"
#include "map.h"
#include "colors.h"
#include "entity.h"
#include "window_manager.h"
#include "game.h"

GraphicsManager::GraphicsManager() 
{
	viewportShape.setSize(wm.viewportSize);
	viewportShape.setPosition(wm.viewportOffset);
	viewportShape.setOutlineColor(colors.red);
	viewportShape.setOutlineThickness(1);
	viewportShape.setFillColor(colors.transparent);

	verticalLine.setSize(Vec2f(wm.lineWidth, wm.gridSize.y + wm.lineWidth));
	verticalLine.setFillColor(colors.grey);

	horizontalLine.setSize(Vec2f(wm.gridSize.x + wm.lineWidth, wm.lineWidth));
	horizontalLine.setFillColor(colors.grey);

	sf::RectangleShape grassRect;
	sf::RectangleShape waterRect;

	grassRect.setSize(wm.tileSize);
	grassRect.setFillColor(colors.green);
	terrainShapes.push_back(grassRect);

	waterRect.setSize(wm.tileSize);
	waterRect.setFillColor(colors.blue);
	terrainShapes.push_back(waterRect);

	entityShape.setSize(wm.entitySize);
	entityShape.setFillColor(colors.white);

	selectionShape.setSize(wm.entitySize);
	selectionShape.setOutlineThickness(wm.lineWidth);
	selectionShape.setOutlineColor(colors.yellow);
	selectionShape.setFillColor(colors.transparent);

	if (!arial.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");
	initText(fpsText, Vec2f(wm.windowPaddingLeft, wm.windowPaddingTop));
	initText(selectionText, wm.rightPannelPosition);
}

void GraphicsManager::draw() {
	wm.window.clear();

	wm.window.setView(wm.mapView);
	
	drawTerrain();
	if (showGrid)
		drawGrid();
	drawEntities();
	wm.window.setView(wm.window.getDefaultView());
	drawViewportOutline();
	drawText();

	wm.window.display();
}

void GraphicsManager::drawTerrain() {
	for (int x = 0; x < map.terrainGrid.size(); ++x) {
		for (int y = 0; y < map.terrainGrid[x].size(); ++y) {
			terrainShapes.at(map.terrainGrid[x][y]).
				setPosition(Vec2f(wm.tileSize.x * float(x), wm.tileSize.y * (float)y));
			wm.window.draw(terrainShapes.at(map.terrainGrid[x][y]));
		}
	}
}

void GraphicsManager::drawEntities() {
	for (int x = 0; x < map.terrainGrid.size(); ++x) {
		for (int y = 0; y < map.terrainGrid[x].size(); ++y) {
			Entity* entity = map.entityGrid[x][y];
			if (entity != nullptr) {
				Vec2f worldPos = wm.tileToWorld(entity->tile) - Vec2f(wm.entitySize.x / 2, wm.entitySize.y / 2);
				entityShape.setPosition(worldPos);
				entityShape.setFillColor(entity->color);
				wm.window.draw(entityShape);
				if (entity->isSelected) {
					selectionShape.setPosition(worldPos);
					wm.window.draw(selectionShape);
				}
			}
		}
	}
}

void GraphicsManager::drawGrid() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(Vec2f(wm.tileSize.x * i - wm.lineWidthHalf, -wm.lineWidthHalf));
		wm.window.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(Vec2f(-wm.lineWidthHalf, wm.tileSize.y * i - wm.lineWidthHalf));
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
	s << "   Actual FPS: " << std::setprecision(3) << wm.actualFPS;
	fpsText.setString(s.str());
	wm.window.draw(fpsText);
}

void GraphicsManager::drawTextSelection() {
	if (selectedEntity != nullptr) {
		std::ostringstream s;
		s << "Entity\n";
		s << "ID: ";
		s << selectedEntity->id;
		selectionText.setString(s.str());
		wm.window.draw(selectionText);
	}
}

void GraphicsManager::drawViewportOutline() {
	wm.window.draw(viewportShape);
}

void GraphicsManager::initText(sf::Text& text, const Vec2f& position) {
	text.setFont(arial);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);
	text.setPosition(position);
}
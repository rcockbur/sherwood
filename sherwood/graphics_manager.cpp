#include <assert.h>
#include <vector>
#include "graphics_manager.h"
#include "map.h"
#include "colors.h"
#include "entity.h"
#include "window_manager.h"

extern bool showGrid;

const float lineWidthHalf = 1;
const float lineWidth = lineWidthHalf * 2;

sf::RectangleShape verticalLine;
sf::RectangleShape horizontalLine;
sf::RectangleShape viewportShape;
sf::RectangleShape entityShape;
sf::Font arial;
sf::Text text;
std::vector<sf::RectangleShape> terrainShapes;

GraphicsManager::GraphicsManager(const Map& _map, WindowManager& wm): 
	map(_map), 
	wm(wm)
{
	viewportShape.setSize(viewportSize);
	viewportShape.setPosition(viewportOffset);
	viewportShape.setOutlineColor(colors.red);
	viewportShape.setOutlineThickness(1);
	viewportShape.setFillColor(colors.transparent);

	verticalLine.setSize(Vec2f(lineWidth, gridSize.y + lineWidth));
	verticalLine.setFillColor(colors.grey);

	horizontalLine.setSize(Vec2f(gridSize.x + lineWidth, lineWidth));
	horizontalLine.setFillColor(colors.grey);

	sf::RectangleShape grassRect;
	sf::RectangleShape waterRect;

	grassRect.setSize(tileSize);
	grassRect.setFillColor(colors.green);
	terrainShapes.push_back(grassRect);

	waterRect.setSize(tileSize);
	waterRect.setFillColor(colors.blue);
	terrainShapes.push_back(waterRect);

	entityShape.setSize(tileSize);
	entityShape.setFillColor(colors.white);

	if (!arial.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");
	text.setFont(arial);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);
	text.setPosition(Vec2f(windowPaddingLeft, windowPaddingTop));
}

void GraphicsManager::draw() {
	wm.window.clear();

	wm.window.setView(wm.mapView);
	drawMap();
	if (showGrid) {
		drawGrid();
	}
	
	wm.window.setView(wm.window.getDefaultView());
	drawViewportOutline();
	drawText();

	wm.window.display();
}

void GraphicsManager::drawMap() {
	for (int x = 0; x < map.terrain_grid.size(); ++x) {
		for (int y = 0; y < map.terrain_grid[x].size(); ++y) {
			terrainShapes.at(map.terrain_grid[x][y]).
				setPosition(Vec2f(tileSize.x * float(x), tileSize.y * (float)y));
			wm.window.draw(terrainShapes.at(map.terrain_grid[x][y]));
			if (map.entity_grid[x][y] != nullptr) {
				entityShape.setPosition(wm.tileToWorld(map.entity_grid[x][y]->tile));
				entityShape.setFillColor(map.entity_grid[x][y]->color);
				wm.window.draw(entityShape);
			}
		}
	}
}

void GraphicsManager::drawGrid() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(Vec2f(tileSize.x * i - lineWidthHalf, -lineWidthHalf));
		wm.window.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(Vec2f(-lineWidthHalf, tileSize.y * i - lineWidthHalf));
		wm.window.draw(horizontalLine);
	}
}

void GraphicsManager::drawText() {
	std::string s("Target FPS: ");
	s += std::to_string(wm.targetFPS);
	s += std::string("  Actual FPS: ");
	s += std::to_string(wm.actualFPS);
	text.setString(s);
	wm.window.draw(text);
}

void GraphicsManager::drawViewportOutline() {
	wm.window.draw(viewportShape);
}

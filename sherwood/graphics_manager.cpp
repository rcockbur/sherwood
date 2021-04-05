#include <assert.h>
#include <vector>
#include "graphics_manager.h"
#include "map.h"
#include "colors.h"
#include "entity.h"

extern uint targetFPS;
extern float actualFPS;

const Vec2u windowSize(600, 600);
const Vec2f viewSize(300, 380);
const Vec2f hudOffset(10, 5);
const Vec2f viewportOffset(hudOffset + Vec2f(0,20));
const Vec2f viewportOffsetRatio(viewportOffset.x / windowSize.x, viewportOffset.y / windowSize.y);
const Vec2f viewportSizeRatio(viewSize.x / windowSize.x, viewSize.y / windowSize.y);
const float lineWidth = 1;
const float lineWidthHalf = lineWidth / 2;
const Vec2f tileSize{ 15,15 };

sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Sherwood");
sf::View mapView(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
sf::RectangleShape verticalLine;
sf::RectangleShape horizontalLine;

sf::RectangleShape viewportRect;
sf::RectangleShape square;
sf::Font arial;
sf::Text text;
std::vector<sf::RectangleShape> terrainRects;

GraphicsManager::GraphicsManager(const Map& _map, sf::Color _color)
	: map(_map), gridColor(_color), gridSize(calculateGridSize(_map.tileCount))
{
	window.setPosition(Vec2i(0, 0));

	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	
	viewportRect.setSize(viewSize);
	viewportRect.setPosition(viewportOffset + Vec2f(1,1));
	viewportRect.setOutlineColor(colors.red);
	viewportRect.setOutlineThickness(1);
	viewportRect.setFillColor(colors.transparent);

	verticalLine.setSize(Vec2f(lineWidth, gridSize.y + lineWidth));
	verticalLine.setFillColor(gridColor);

	horizontalLine.setSize(Vec2f(gridSize.x + lineWidth, lineWidth));
	horizontalLine.setFillColor(gridColor);

	sf::RectangleShape grassRect;
	sf::RectangleShape waterRect;

	grassRect.setSize(tileSize);
	grassRect.setFillColor(colors.green);
	terrainRects.push_back(grassRect);

	waterRect.setSize(tileSize);
	waterRect.setFillColor(colors.blue);
	terrainRects.push_back(waterRect);

	square.setSize(Vec2f(tileSize) - Vec2f(lineWidth, lineWidth));
	square.setFillColor(colors.white);

	if (!arial.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");
	text.setFont(arial);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);
	text.setPosition(hudOffset);
}

void GraphicsManager::draw() {
	window.clear();

	window.setView(mapView);
	drawMap();
	drawGrid();

	window.setView(window.getDefaultView());
	drawViewportOutline();
	drawText();

	window.display();
}

void GraphicsManager::drawMap() {
	
	for (int x = 0; x < map.terrain_grid.size(); ++x) {
		for (int y = 0; y < map.terrain_grid[x].size(); ++y) {
			terrainRects.at(map.terrain_grid[x][y]).
				setPosition(Vec2f(tileSize.x * float(x), tileSize.y * (float)y));
			window.draw(terrainRects.at(map.terrain_grid[x][y]));
			if (map.entity_grid[x][y] != nullptr) {
				square.setPosition(tileToWorld(map.entity_grid[x][y]->tile));
				square.setFillColor(map.entity_grid[x][y]->color);
				window.draw(square);
			}
		}
	}
}

void GraphicsManager::drawGrid() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(Vec2f(tileSize.x * i - lineWidthHalf, -lineWidthHalf));
		window.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(Vec2f(-lineWidthHalf, tileSize.y * i - lineWidthHalf));
		window.draw(horizontalLine);
	}
}

void GraphicsManager::drawText() {
	std::string s("Target FPS: ");
	s += std::to_string(targetFPS);
	s += std::string("  Actual FPS: ");
	s += std::to_string(actualFPS);
	text.setString(s);
	window.draw(text);
}

void GraphicsManager::drawViewportOutline() {
	window.draw(viewportRect);
}

Vec2f GraphicsManager::tileToWorld(const Vec2i tile) {
	return Vec2f((float)tile.x * tileSize.x + lineWidthHalf, (float)tile.y * tileSize.y + lineWidthHalf);
}

Vec2f GraphicsManager::calculateGridSize(const Vec2i& _tileCount) {
	return Vec2f(((float)_tileCount.x) * tileSize.x, ((float)_tileCount.y) * tileSize.y);
}
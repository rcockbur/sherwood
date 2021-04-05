#include <assert.h>
#include <vector>
#include "graphics_manager.h"
#include "map.h"
#include "colors.h"
#include "entity.h"

extern uint targetFPS;
extern float actualFPS;
extern bool showGrid;

const Vec2f tileSize{ 24,24 };
const Vec2u windowSize(800, 450);
const float windowPaddingTop = 5;
const float windowPaddingLeft = 5;
const float windowPaddingBot = 10;
const float topPanelHeight = 20;
const float viewportWidth = 580;
const float lineWidthHalf = 1;
const float lineWidth = lineWidthHalf * 2;

const Vec2f viewportSize(viewportWidth, windowSize.y - windowPaddingTop - windowPaddingBot - topPanelHeight);
const Vec2f viewportOffset(Vec2f(windowPaddingLeft, windowPaddingTop + topPanelHeight));
const Vec2f viewportOffsetRatio(viewportOffset.x / windowSize.x, viewportOffset.y / windowSize.y);
const Vec2f viewportSizeRatio(viewportSize.x / windowSize.x, viewportSize.y / windowSize.y);
const Vec2f viewSize(viewportSize);

sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Sherwood");
sf::View mapView(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
sf::RectangleShape verticalLine;
sf::RectangleShape horizontalLine;

sf::RectangleShape viewportShape;
sf::RectangleShape entityShape;
sf::Font arial;
sf::Text text;
std::vector<sf::RectangleShape> terrainShapes;

GraphicsManager::GraphicsManager(const Map& _map, sf::Color _color)
	: map(_map), gridColor(_color), gridSize(calculateGridSize(_map.tileCount))
{
	window.setPosition(Vec2i(0, 0));

	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	
	viewportShape.setSize(viewportSize);
	viewportShape.setPosition(viewportOffset);
	viewportShape.setOutlineColor(colors.red);
	viewportShape.setOutlineThickness(1);
	viewportShape.setFillColor(colors.transparent);

	verticalLine.setSize(Vec2f(lineWidth, gridSize.y + lineWidth));
	verticalLine.setFillColor(gridColor);

	horizontalLine.setSize(Vec2f(gridSize.x + lineWidth, lineWidth));
	horizontalLine.setFillColor(gridColor);

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
	window.clear();

	window.setView(mapView);
	drawMap();
	if (showGrid) {
		drawGrid();
	}
	
	window.setView(window.getDefaultView());
	drawViewportOutline();
	drawText();

	window.display();
}

void GraphicsManager::drawMap() {
	for (int x = 0; x < map.terrain_grid.size(); ++x) {
		for (int y = 0; y < map.terrain_grid[x].size(); ++y) {
			terrainShapes.at(map.terrain_grid[x][y]).
				setPosition(Vec2f(tileSize.x * float(x), tileSize.y * (float)y));
			window.draw(terrainShapes.at(map.terrain_grid[x][y]));
			if (map.entity_grid[x][y] != nullptr) {
				entityShape.setPosition(tileToWorld(map.entity_grid[x][y]->tile));
				entityShape.setFillColor(map.entity_grid[x][y]->color);
				window.draw(entityShape);
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
	window.draw(viewportShape);
}

Vec2f GraphicsManager::tileToWorld(const Vec2i tile) {
	return Vec2f((float)tile.x * tileSize.x, (float)tile.y * tileSize.y);
}

Vec2i GraphicsManager::worldToTile(const Vec2f pos) {
	return Vec2i((int)(pos.x / tileSize.x), (int)(pos.y / tileSize.y));
}

Vec2f GraphicsManager::calculateGridSize(const Vec2i& _tileCount) {
	return Vec2f(((float)_tileCount.x) * tileSize.x, ((float)_tileCount.y) * tileSize.y);
}

void GraphicsManager::handleClick(const Vec2f screenPosition)
{
	std::cout << "ScreenPosition:" << screenPosition.x << "," << screenPosition.y << "\n";

	sf::Rect<float> viewportRect(viewportOffset, viewportSize + Vec2f(0,0));

	if (viewportRect.contains(screenPosition)) {
		Vec2f worldPosition = window.mapPixelToCoords(Vec2i((int)(screenPosition.x + 0.5f), (int)(screenPosition.y + 0.5f)), mapView);
		std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
		Vec2i clickedTile = worldToTile(worldPosition);
		std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
	}
	else {
		std::cout << "Out of bounds\n";
	}
}
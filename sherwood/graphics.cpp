#include "graphics.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include "utility.h"
#include <string>
#include <iostream>

extern Map map;
extern EntityManager em;
extern uint targetFPS;
extern float actualFPS;

Colors colors;
Vec2f windowSize(600, 600);
Vec2f viewSize(300, 380);
Vec2f hudOffset(10, 5);
Vec2f viewportOffset(hudOffset + Vec2f(0,20));
Vec2f viewportOffsetRatio(viewportOffset.x / windowSize.x, viewportOffset.y / windowSize.y);
Vec2f viewportSizeRatio(viewSize.x / windowSize.x, viewSize.y / windowSize.y);

sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Sherwood");
sf::View mapView(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
sf::RectangleShape verticalLine;
sf::RectangleShape horizontalLine;
sf::RectangleShape grassRect;
sf::RectangleShape waterRect;
sf::RectangleShape viewportRect;
sf::RectangleShape square;
sf::Font arial;
sf::Text text;

void initGraphics() {
	window.setPosition(Vec2i(0, 0));
	updateFPS(targetFPS);

	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	
	viewportRect.setSize(viewSize);
	viewportRect.setPosition(viewportOffset + Vec2f(1,1));
	viewportRect.setOutlineColor(colors.red);
	viewportRect.setOutlineThickness(1);
	viewportRect.setFillColor(colors.transparent);

	verticalLine.setSize(Vec2f(map.lineWidth, map.gridSize.y + map.lineWidth));
	verticalLine.setFillColor(map.color);

	horizontalLine.setSize(Vec2f(map.gridSize.x + map.lineWidth, map.lineWidth));
	horizontalLine.setFillColor(map.color);

	grassRect.setSize(map.tileSize);
	grassRect.setFillColor(colors.green);

	waterRect.setSize(map.tileSize);
	waterRect.setFillColor(colors.blue);

	square.setSize(Vec2f(map.tileSize) - Vec2f(map.lineWidth, map.lineWidth));
	square.setFillColor(colors.white);

	if (!arial.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");
	text.setFont(arial);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);
	text.setPosition(hudOffset);
}

void drawAll() {
	window.clear();
	window.setView(mapView);
	drawTerrain();
	drawGrid();
	drawEntities();
	window.setView(window.getDefaultView());
	drawViewportOutline();
	drawText();
	window.display();
}

void drawTerrain() {
	
	for (int x = 0; x < map.terrain_grid.size(); ++x) {
		for (int y = 0; y < map.terrain_grid[x].size(); ++y) {
			if (map.terrain_grid[x][y] == 0) {
				waterRect.setPosition(Vec2f(map.tileSize.x * float(x), map.tileSize.y * (float)y));
				window.draw(waterRect);
			} else {
				grassRect.setPosition(Vec2f(map.tileSize.x * float(x), map.tileSize.y * (float)y));
				window.draw(grassRect);
			}
		}
	}
}

void drawGrid() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(Vec2f(map.tileSize.x * i - map.lineWidthHalf, -map.lineWidthHalf));
		window.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(Vec2f(-map.lineWidthHalf, map.tileSize.y * i - map.lineWidthHalf));
		window.draw(horizontalLine);
	}
}

void drawEntities() {
	for (auto& entity : em.getEntities()) {
		square.setPosition(tileToWorld(entity->tile));
		square.setFillColor(entity->color);
		window.draw(square);
	}
}

void drawText() {
	std::string s("Target FPS: ");
	s += std::to_string(targetFPS);
	s += std::string("  Actual FPS: ");
	s += std::to_string(actualFPS);
	text.setString(s);
	window.draw(text);
}

void drawViewportOutline() {
	window.draw(viewportRect);
}

void updateFPS(uint fps) {
	targetFPS = fps;
	window.setFramerateLimit(targetFPS);
}
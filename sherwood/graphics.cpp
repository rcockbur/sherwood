#include "graphics.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include "utility.h"
#include <string>


extern Map map;
extern EntityManager em;
extern sf::RenderWindow window;
extern uint targetFPS;
sf::RectangleShape verticalLine;
sf::RectangleShape horizontalLine;
sf::RectangleShape square;
sf::Font arial;
sf::Text text;

void initGraphics() {
	window.setPosition(Vec2i(0, 0));
	verticalLine.setSize(Vec2f(map.lineWidth, map.gridSize.y + map.lineWidth));
	verticalLine.setFillColor(map.color);
	horizontalLine.setSize(Vec2f(map.gridSize.x + map.lineWidth, map.lineWidth));
	horizontalLine.setFillColor(map.color);
	square.setSize(Vec2f(map.tileSize) - Vec2f(map.lineWidth, map.lineWidth));
	square.setFillColor(sf::Color::Blue);
	if (!arial.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");
	text.setFont(arial);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setPosition(Vec2f(1, 1));
}

void drawMap() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(worldToScreen(Vec2f(map.tileSize.x * i - map.lineWidthHalf, -map.lineWidthHalf)));
		window.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(worldToScreen(Vec2f(-map.lineWidthHalf, map.tileSize.y * i - map.lineWidthHalf)));
		window.draw(horizontalLine);
	}
}

void drawEntities() {
	for (auto& entity : em.getEntities()) {
		square.setPosition(tileToScreen(entity->tile));
		square.setFillColor(entity->color);
		window.draw(square);
	}
}

void drawText() {
	std::string s("targetFPS:");
	s += std::to_string(targetFPS);
	text.setString(s);
	window.draw(text);
}
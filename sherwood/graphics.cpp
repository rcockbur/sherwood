#include "graphics.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include "utility.h"

extern Map map;
extern EntityManager em;
extern sf::RenderWindow window;
sf::RectangleShape verticalLine;
sf::RectangleShape horizontalLine;

void initGraphics() {
	window.setPosition(Vec2i(0, 0));
	verticalLine.setSize(Vec2f(map.lineWidth, map.gridSize.y + map.lineWidth));
	verticalLine.setFillColor(map.color);
	horizontalLine.setSize(Vec2f(map.gridSize.x + map.lineWidth, map.lineWidth));
	horizontalLine.setFillColor(map.color);
}

void drawMap() {
	for (int i = 0; i < map.tileCount.x + 1; i++) {
		verticalLine.setPosition(worldToScreen(Vec2f(map.tileSize.x * i, 0)));
		window.draw(verticalLine);
	}
	for (int i = 0; i < map.tileCount.y + 1; i++) {
		horizontalLine.setPosition(worldToScreen(Vec2f(0, map.tileSize.y * i)));
		window.draw(horizontalLine);
	}
}
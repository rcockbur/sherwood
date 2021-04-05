#pragma once
#include "globals.h"

class Map;

class GraphicsManager {
public:
	GraphicsManager(const Map& map, sf::Color color);
	void draw();
	void handleClick(const Vec2f screenPosition);
private:
	const Map& map;
	const Vec2f gridSize;
	const sf::Color gridColor;
	void drawMap();
	void drawGrid();
	void drawViewportOutline();
	void drawText();
	Vec2f tileToWorld(const Vec2i);
	Vec2i worldToTile(const Vec2f);
	Vec2f calculateGridSize(const Vec2i& tileCount);
};


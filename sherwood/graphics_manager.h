#pragma once
#include "globals.h"
#include "graphics_manager.h"


class Map;

class GraphicsManager {
public:
	GraphicsManager(const Map& map, sf::Color color);
	void draw();
private:
	const Map& map;
	const Vec2f gridSize;
	const sf::Color gridColor;
	void drawMap();
	void drawGrid();
	void drawViewportOutline();
	void drawText();
	Vec2f tileToWorld(const Vec2i);
	Vec2f calculateGridSize(const Vec2i& tileCount);
};



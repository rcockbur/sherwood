#pragma once
#include "globals.h"

class Map;
class WindowManager;

class GraphicsManager {
public:
	GraphicsManager(const Map& map, WindowManager& wm);
	void draw();
private:
	const Map& map;
	WindowManager& wm;
	
	const sf::Color gridColor;
	void drawMap();
	void drawGrid();
	void drawViewportOutline();
	void drawText();
	Vec2f calculateGridSize(const Vec2i& tileCount);
};


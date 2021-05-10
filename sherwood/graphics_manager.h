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
	void drawTerrain();
	void drawEntities();
	void drawGrid();
	void drawViewportOutline();
	void drawText();
	void drawTextFPS();
	void drawTextSelection();
	Vec2f calculateGridSize(const Vec2i& tileCount);
	void initText(sf::Text& text, const Vec2f& position);
};


#pragma once
#include "types.h"

class Map;
class WindowManager;

class GraphicsManager {
public:
	GraphicsManager();
	void draw();
private:
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
	sf::RectangleShape verticalLine;
	sf::RectangleShape horizontalLine;
	sf::RectangleShape viewportShape;
	sf::RectangleShape entityShape;
	sf::RectangleShape selectionShape;
	sf::Font arial;
	sf::Text fpsText;
	sf::Text selectionText;
	std::vector<sf::RectangleShape> terrainShapes;
};


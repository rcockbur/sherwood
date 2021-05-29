#pragma once
#include "types.h"
#include "node.h"
#include <list>

class Map;
class WindowManager;

class GraphicsManager {
public:
	GraphicsManager();
	void draw();
	void drawPathDebug(const std::list<node>& open, const std::list<node>& closed, const Vec2i& s, 
		const Vec2i& e, std::list<Vec2i> * path);
private:
	void initText(sf::Text& text, const Vec2f& position);
	void drawWorld();
	void drawHUD();
	void drawTerrain();
	void drawEntities();
	void drawGrid();
	void drawViewportOutline();
	void drawText();
	void drawTextFPS();
	void drawTextSelection();
	
	Vec2f calculateGridSize(const Vec2i& tileCount);
	
	const sf::Color gridColor;
	sf::RectangleShape verticalLine;
	sf::RectangleShape horizontalLine;
	sf::RectangleShape viewportShape;
	sf::RectangleShape entityShape;
	sf::RectangleShape selectionShape;
	sf::RectangleShape pathDebugShape;
	sf::Font arial;
	sf::Text fpsText;
	sf::Text selectionText;
	std::vector<sf::RectangleShape> terrainShapes;
};


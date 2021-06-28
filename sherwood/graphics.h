#pragma once
#include "types.h"
#include "node.h"
#include <list>

class Map;
class Window;

class Graphics {
public:
	Graphics();
	void draw();
	void drawSearchDebug(const std::list<node>& open, const std::list<node>& closed, const Vec2i& s, 
		const Vec2i& e, std::list<Vec2i> * path);
private:
	const sf::Color gridColor;
	sf::RectangleShape verticalLine;
	sf::RectangleShape horizontalLine;
	sf::RectangleShape viewportShape;
	sf::CircleShape pathDebugShape;
	sf::Font arial;
	sf::Text fpsText;
	sf::Text selectionText;
	std::vector<sf::RectangleShape> terrainShapes;

	void initText(sf::Text& text, const Vec2f& position);
	void drawWorld();
	void drawHUD();
	void drawTerrain();
	void drawEntities();
	void drawGrid();
	void drawViewportOutline();
	void drawText();
	void drawTopText();
	void drawTextSelection();
	void drawSearchNodes(const std::list<node>& nodes, const Color& color);
	void drawSearchPath(const std::list<Vec2i>& path, const Color& color);
	void drawSearchTile(const Vec2i& node, const Color& color);
};


#pragma once
#include "types.h"
#include "node.h"
#include <list>
#include "panel.h"

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
	sf::CircleShape pathDebugShape;
	std::vector<sf::RectangleShape> terrainShapes;

	void drawWorld();
	void drawTerrain();
	void drawGrid();
	void drawEntities();

	void drawHUD();
	void updateText();

	void drawSearchNodes(const std::list<node>& nodes, const Color& color);
	void drawSearchPath(const std::list<Vec2i>& path, const Color& color);
	void drawSearchTile(const Vec2i& node, const Color& color);
};


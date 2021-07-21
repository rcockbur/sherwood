#pragma once
#include "types.h"
#include "node.h"
#include <list>
#include <set>

class Map;
class Window;

class Graphics {
public:
	Graphics();
	void draw();
	void drawAStar(const std::vector<AStarOpenTuple>& open, const std::set<Vec2i, CompareVec2i>& closed,
		const Vec2i& s, const Vec2i& e, const Vec2i* current, std::list<Vec2i>* path);
	void drawBreadthFirst(const std::list<node2>& open, const std::list<node2>& closed, const Vec2i& s,
		const Vec2i& e, std::list<Vec2i>* path);
	void drawBreadthFirstNew(const std::vector<BreadthFirstOpenTuple>& open, const std::set<Vec2i, CompareVec2i>& closed,
		const Vec2i& s, const Vec2i* e, const Vec2i* current, std::list<Vec2i>* path);

private:
	const Color gridColor;
	RectangleShape verticalLine;
	RectangleShape horizontalLine;
	CircleShape pathDebugShape;
	std::vector<RectangleShape> terrainShapes;

	void drawWorld();
	void drawTerrain();
	void drawGrid();
	void drawEntities();

	void drawHUD();
	void updateText();

	void drawSearchNodes(const std::list<node>& nodes, const Color& color);
	void drawSearchNodes2(const std::list<node2>& nodes, const Color& color);
	void drawSearchPath(const std::list<Vec2i>& path, const Color& color);
	void drawSearchTile(const Vec2i node, const Color& color);
	void drawDebugTile(const Vec2i tile);

	void drawAStarOpen(const std::vector<AStarOpenTuple>& open, const Color& color);
	void drawBreadthFirstOpen(const std::vector<BreadthFirstOpenTuple>& open, const Color& color);
	void drawClosed(const std::set<Vec2i, CompareVec2i>& closed, const Color& color);
};


#pragma once
#include "types.h"
#include <list>
#include <set>

class Graphics {
public:
	Graphics();
	void draw();
	void drawAStar(const Vec2i* current, std::list<Vec2i>* path);
	void drawBreadthFirst(const Vec2i* end, const Vec2i* current, std::list<Vec2i>* path);

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

	void drawAStarOpen(const std::vector<AStarOpenTuple>& open, const Color& color);
	void drawBreadthFirstOpen(const std::vector<BreadthFirstOpenTuple>& open, const Color& color);
	void drawClosed(const std::set<Vec2i, CompareVec2i>& closed, const Color& color);
	void drawSearchPath(const std::list<Vec2i>& path, const Color& color);
	void drawSearchTile(const Vec2i node, const Color& color);
};


#pragma once
#include "types.h"
#include <list>
#include <queue>
#include "node.h"


class aStar {
public:
    Vec2i start;
    Vec2i end;
    Vec2i neighbours[8];
    std::list<node> open;
    int tilesChecked;
    std::list<node> closed;
	aStar();
    int heuristic(Vec2i& p);
    bool existVec2i(Vec2i& p, int cost);
    void fillOpen(node& n);
    bool search(Vec2i& s, Vec2i& e);
    int path(std::list<Vec2i>& path);
    void clear();
private:
    void drawDebug();
};
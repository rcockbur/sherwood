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
    bool search(const Vec2i& s, const Vec2i& e);
    std::list<Vec2i> path();
    void clear();
private:
    bool orthoginalNeighborIsPathable(const Vec2i);
    int heuristic(const Vec2i& p);
    bool checkNeighbor(Vec2i& p, int cost);
    void fillOpen(node& n);
};
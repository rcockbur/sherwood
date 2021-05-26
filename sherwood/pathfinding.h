#pragma once
#include "types.h"
#include <list>

class node {
public:
    bool operator == (const node& o);
    bool operator == (const Vec2i& o);
    bool operator < (const node& o);
    Vec2i pos, parent;
    int h, g;
};

class aStar {
public:
    Vec2i start;
    Vec2i end;
    Vec2i neighbours[8];
    std::list<node> open;
    std::list<node> closed;
	aStar();
    int calcDist(Vec2i& p);
    bool existVec2i(Vec2i& p, int cost);
    bool fillOpen(node& n);
    bool search(Vec2i& s, Vec2i& e);
    int path(std::list<Vec2i>& path);
    void clear();
};
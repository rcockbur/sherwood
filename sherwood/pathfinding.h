#pragma once
#include "types.h"
#include <list>
#include <map>
#include <vector>
#include <set>

class Fixed;
class FixedStyle;

class Pathfinder {
public:
    Vec2i start;
    Vec2i end;
    std::set<Vec2i, CompareVec2i> closed;
protected:
    std::set<int> pathableTypes;
    TileIntMap costSoFar;
    TileTileMap cameFrom;
    bool tileIsPathable(const Vec2i _tile) const;
    bool orthoginalNeighborIsPathable(const Vec2i);
    bool validDiagonal(const Vec2i& source, const Vec2i& direction) const;
};

class AStar : public Pathfinder {
public:
    std::vector<AStarOpenTuple> open;
    int tilesChecked;
    AStar();
    bool search(const Vec2i& s, const Vec2i& e, std::set<int> pathableTypes);
    std::list<Vec2i> path();
private:
    void clear();
    int heuristic(const Vec2i& p);
};

class BreadthFirst : public Pathfinder {
public:
    std::vector<BreadthFirstOpenTuple> open;
    Fixed* search(const Vec2i& s, const FixedStyle& fet, std::set<int> pathableTypes);
    std::list<Vec2i> path();
    void clear();
private:
};
#pragma once
#include "types.h"
#include <list>
#include "node.h"
#include <map>
#include <queue>
#include <vector>
#include <set>

class Building;



class AStar {
public:
    Vec2i start;
    Vec2i end;
    std::vector<AStarOpenTuple> open;
    std::set<Vec2i, CompareVec2i> closed;
    TileIntMap costSoFar;
    TileTileMap cameFrom;
    int tilesChecked;
    AStar();
    bool searchForTile(const Vec2i& s, const Vec2i& e);
    std::list<Vec2i> path();
    
private:
    void clear();
    bool orthoginalNeighborIsPathable(const Vec2i);
    int heuristic(const Vec2i& p);
};

class NewBreadthFirst {
public:
    Vec2i start;
    Vec2i end;
    std::vector<BreadthFirstOpenTuple> open;
    std::set<Vec2i, CompareVec2i> closed;
    TileIntMap costSoFar;
    TileTileMap cameFrom;
    NewBreadthFirst();
    Building* searchForHouse(const Vec2i& s);
    std::list<Vec2i> path();
    void clear();
private:
    bool orthoginalNeighborIsPathable(const Vec2i);
    int heuristic(const Vec2i& p);
};
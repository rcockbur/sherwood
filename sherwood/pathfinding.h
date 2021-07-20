#pragma once
#include "types.h"
#include <list>
#include "node.h"
#include <map>
#include <queue>
#include <vector>
#include <set>

class Building;



class aStar {
public:
    Vec2i start;
    Vec2i end;
    std::list<node> open;
    int tilesChecked;
    std::list<node> closed;
	aStar();
    bool searchForTile(const Vec2i& s, const Vec2i& e);
    std::list<Vec2i> path();
    void clear();
private:
    bool orthoginalNeighborIsPathable(const Vec2i);
    int heuristic(const Vec2i& p);
    bool checkNeighbor(Vec2i& p, int cost);
    void fillOpen(node& n);
};

class NewAStar {
public:
    
    Vec2i start;
    Vec2i end;
    //PriorityQueue open;
    std::vector<Tuple> open;
    std::set<Vec2i, CompareVec2i> closed;
    TileIntMap costSoFar;
    TileTileMap cameFrom;
    int tilesChecked;
    //std::list<node> closed;
    NewAStar();
    bool searchForTile(const Vec2i& s, const Vec2i& e);
    std::list<Vec2i> path();
    void clear();
private:
    bool orthoginalNeighborIsPathable(const Vec2i);
    int heuristic(const Vec2i& p);
    //bool checkNeighbor(Vec2i& p, int cost);
    void fillOpen(node& n);
};

class breadthFirst {
public:
    Vec2i start;
    Vec2i end;
    std::list<node2> open;
    int tilesChecked;
    std::list<node2> closed;
    breadthFirst();
    Building* searchForHouse(const Vec2i& s);
    std::list<Vec2i> path();
    void clear();
private:
    bool orthoginalNeighborIsPathable(const Vec2i);
    int heuristic(const Vec2i& p);
    bool checkNeighbor(Vec2i& p, int cost);
    void fillOpen(node2& n);
};
#include "pathfinding.h"
#include "globals.h"
#include "graphics.h"
#include "color.h"
#include <Windows.h>
#include <cmath>

aStar::aStar() {
    tilesChecked = 0;
    neighbours[0] = Vec2i(-1, -1); 
    neighbours[1] = Vec2i(1, -1);
    neighbours[2] = Vec2i(-1, 1); 
    neighbours[3] = Vec2i(1, 1);
    neighbours[4] = Vec2i(0, -1); 
    neighbours[5] = Vec2i(-1, 0);
    neighbours[6] = Vec2i(0, 1); 
    neighbours[7] = Vec2i(1, 0);
}
int aStar::heuristic(const Vec2i& p) {
    int deltaX = std::abs(end.x - p.x);
    int deltaY = std::abs(end.y - p.y);
    int diagonals = std::min(deltaX, deltaY);
    int orthoginals = std::abs(deltaX - deltaY);
    return 14 * diagonals + 10 * orthoginals;
}

bool aStar::checkNeighbor(Vec2i& p, int neighborF) {
    std::list<node>::iterator i;
    i = std::find(open.begin(), open.end(), p);
    if (i != open.end()) {
        if ((*i).f < neighborF) {
            return true;
        }
        else { 
            open.erase(i); 
            return false; 
        }
    }
    return false;
}

bool validDiagonal(const Vec2i& source, const Vec2i& direction) {
    Vec2i tile1(source.x, source.y + direction.y);
    Vec2i tile2(source.x + direction.x, source.y);
    return map.isPathable(tile1) && map.isPathable(tile2);
}

void aStar::fillOpen(node& n) {
    int stepCost;
    int neighborF;
    int neighborG;
    int neighborH;
    Vec2i neighbourTile;
    for (int x = 0; x < 8; x++) {
        stepCost = x < 4 ? 14 : 10;
        neighbourTile = n.tile + neighbours[x];
        std::list<node>::iterator i;
        i = std::find(closed.begin(), closed.end(), neighbourTile);
        if (i == closed.end()) {
            if (map.isWithinBounds(neighbourTile) && map.isPathable(neighbourTile)) {
                if (x >= 4 || validDiagonal(n.tile, neighbours[x])) {
                    neighborG = stepCost + n.g;
                    neighborH = heuristic(neighbourTile);
                    neighborF = neighborG + neighborH;
                    if (!checkNeighbor(neighbourTile, neighborF)) {
                        node m;
                        tilesChecked++;
                        m.tieRating = tilesChecked;
                        m.f = neighborF;
                        m.g = neighborG;
                        m.h = neighborH;
                        m.tile = neighbourTile;
                        m.parent = n.tile;
                        open.push_back(m);
                    }
                }
            }
        }
    }
}

bool aStar::search(const Vec2i& s, const Vec2i& e) {
    if (map.isPathable(e)) {
        node n;
        end = e;
        start = s;
        tilesChecked = 0;
        n.g = 0;
        n.tile = s;
        n.parent = Vec2i(-1, -1);
        n.h = heuristic(s);
        n.f = n.h + n.g;
        n.tieRating = tilesChecked;
        open.push_back(n);
                 
        while (!open.empty()) {
            open.sort();
            node n = open.front();
            open.pop_front();
            closed.push_back(n);
            if (n == end) {
                if (showPathfinding) Sleep(200); //after completing search successfully
                return true;
            }
            fillOpen(n);
            if (showPathfinding) graphics.drawPathDebug(open, closed, start, end, nullptr);//after each node
        }
        if (showPathfinding) Sleep(200); //after completing search
            
    }
    return false;
}
std::list<Vec2i> aStar::path() {
    std::list<Vec2i> path;
    path.push_front(end);
    path.push_front(closed.back().tile);
    Vec2i parent = closed.back().parent;
    for (std::list<node>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++) {
        if ((*i).tile == parent && !((*i).tile == start)) {
            path.push_front((*i).tile);
            parent = (*i).parent;
            if (showPathfinding) {
                graphics.drawPathDebug(open, closed, start, end, &path);
                Sleep(10); //after each path node
            }
        }
    }
    if (showPathfinding) Sleep(200); //after completing search
        
    return path;
}

void aStar::clear() {
    open.clear();
    closed.clear();
}

void aStar::drawDebug() {

}
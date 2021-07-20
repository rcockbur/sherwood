#include "pathfinding.h"
#include "globals.h"
#include "graphics.h"
#include "color.h"
#include <Windows.h>
#include <cmath>
#include <algorithm>
#include <chrono>

Vec2i neighbours[8] = {
    Vec2i(-1, -1),
    Vec2i(1, -1),
    Vec2i(-1, 1),
    Vec2i(1, 1),
    Vec2i(0, -1),
    Vec2i(-1, 0),
    Vec2i(0, 1),
    Vec2i(1, 0)
};



bool validDiagonal(const Vec2i& source, const Vec2i& direction) {
    Vec2i tile1(source.x, source.y + direction.y);
    Vec2i tile2(source.x + direction.x, source.y);
    return map.isPathable(tile1) && map.isPathable(tile2);
}


aStar::aStar() {
    tilesChecked = 0;
}

bool aStar::orthoginalNeighborIsPathable(const Vec2i tile) {
    Vec2i neighbourTile;
    for (int x = 4; x < 8; x++) {
        neighbourTile = tile + neighbours[x];
        if (map.isWithinBounds(neighbourTile) && map.isPathable(neighbourTile))
            return true;
    }
    return false;
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
            if (map.isWithinBounds(neighbourTile)) {
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

bool aStar::searchForTile(const Vec2i& s, const Vec2i& e) {
    auto begin = std::chrono::high_resolution_clock::now();
    clear();
    if (showPathfinding) renderWindow.setFramerateLimit(1000);
    bool pathFound = false;
    if (map.isPathable(e) || orthoginalNeighborIsPathable(e)) {
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
                pathFound = true;
                break;
            }
            if (map.isPathable(n.tile))
                fillOpen(n);
            if (showPathfinding) {
                graphics.drawSearchDebug(open, closed, start, end, nullptr);//after each node
                //Sleep(50); //after each path node
            }
                
        }     
    }
    if (showPathfinding) renderWindow.setFramerateLimit(targetFPS);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    return pathFound;
}

std::list<Vec2i> aStar::path() {
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(1000);
    }
    std::list<Vec2i> path;
    path.push_front(closed.back().tile);
    Vec2i parent = closed.back().parent;
    for (std::list<node>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++) {
        if ((*i).tile == parent && !((*i).tile == start)) {
            path.push_front((*i).tile);
            parent = (*i).parent;
            if (showPathfinding) {
                graphics.drawSearchDebug(open, closed, start, end, &path);
                Sleep(5); //after each path node
            }
        }
    }
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(targetFPS);
    }
    if (map.isPathable(path.back()) == false) {
        path.pop_back();
    }
    
    return path;
}

void aStar::clear() {
    open.clear();
    closed.clear();
}




NewAStar::NewAStar() {
    tilesChecked = 0;
    //closed.resize(map.size.x * map.size.y, false);
}

bool NewAStar::orthoginalNeighborIsPathable(const Vec2i tile) {
    Vec2i neighbourTile;
    for (int x = 4; x < 8; x++) {
        neighbourTile = tile + neighbours[x];
        if (map.isWithinBounds(neighbourTile) && map.isPathable(neighbourTile))
            return true;
    }
    return false;
}

int NewAStar::heuristic(const Vec2i& p) {
    int deltaX = std::abs(end.x - p.x);
    int deltaY = std::abs(end.y - p.y);
    int diagonals = std::min(deltaX, deltaY);
    int orthoginals = std::abs(deltaX - deltaY);
    return 14 * diagonals + 10 * orthoginals;
}

bool NewAStar::searchForTile(const Vec2i& s, const Vec2i& e) {
    if (showPathfinding) renderWindow.setFramerateLimit(1000);
    auto begin = std::chrono::high_resolution_clock::now();
    bool pathFound = false;
    int mapWidth = map.size.x;
    if (map.isPathable(e) || orthoginalNeighborIsPathable(e)) {
        clear();
        end = e;
        start = s;
        tilesChecked = 0;
        open.push_back(Tuple(0, tilesChecked, start));
        std::push_heap(open.begin(), open.end(), CompareTuple());
        tilesChecked++;
        cameFrom[start] = start;
        costSoFar[start] = 0;

        while (!open.empty()) {
            Vec2i best = std::get<2>(open.front());
            std::pop_heap(open.begin(), open.end(), CompareTuple());
            open.pop_back();
            closed.insert(best);
            if (best == end) {
                pathFound = true;
                break;
            }
            if (map.isPathable(best)) {
                Vec2i neighbor;
                for (int x = 0; x < 8; x++) {
                    neighbor = best + neighbours[x];
                    if (closed.find(neighbor) == closed.end()) {
                        if (map.isWithinBounds(neighbor)) {
                            if (x >= 4 || validDiagonal(best, neighbours[x])) {
                                int stepCost = x < 4 ? 14 : 10;
                                int newCost = costSoFar[best] + stepCost;
                                if (costSoFar.find(neighbor) == costSoFar.end() || newCost < costSoFar[neighbor]) {
                                    costSoFar[neighbor] = newCost;
                                    cameFrom[neighbor] = best;
                                    std::vector<Tuple>::iterator i;
                                    i = std::find_if(open.begin(), open.end(), [&](Tuple t) { return std::get<2>(t) == neighbor; });
                                    if (i == open.end()) {
                                        open.push_back(Tuple(newCost + heuristic(neighbor), tilesChecked, neighbor));
                                        std::push_heap(open.begin(), open.end(), CompareTuple());
                                        tilesChecked++;
                                    }
                                    else {
                                        std::get<0>(*i) = newCost + heuristic(neighbor);
                                        std::get<1>(*i) = tilesChecked;
                                        tilesChecked++;
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
            if (showPathfinding) {
                graphics.drawNewAstar(open, closed, start, end, &best, nullptr);//after each node
                //Sleep(20); //after each path node
            }
                
        }
    }
    if (showPathfinding) renderWindow.setFramerateLimit(targetFPS);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    return pathFound;
}

std::list<Vec2i> NewAStar::path() {
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(1000);
    }
    std::list<Vec2i> path;
    Vec2i current = end;
    while (current != start) {
        path.push_front(current);
        current = cameFrom[current];
        if (showPathfinding) {
            graphics.drawNewAstar(open, closed, start, end, &current, &path);
            Sleep(5); //after each path node
        }
    }
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(targetFPS);
    }
    if (map.isPathable(path.back()) == false) {
        path.pop_back();
    }

    return path;
}

void NewAStar::clear() {
    open.clear();
    //std::fill(closed.begin(), closed.end(), false);
    closed.clear();
    costSoFar.clear();
    cameFrom.clear();
}




breadthFirst::breadthFirst() {
    tilesChecked = 0;

}

bool breadthFirst::orthoginalNeighborIsPathable(const Vec2i tile) {
    Vec2i neighbourTile;
    for (int x = 4; x < 8; x++) {
        neighbourTile = tile + neighbours[x];
        if (map.isWithinBounds(neighbourTile) && map.isPathable(neighbourTile))
            return true;
    }
    return false;
}

int breadthFirst::heuristic(const Vec2i& p) {
    int deltaX = std::abs(end.x - p.x);
    int deltaY = std::abs(end.y - p.y);
    int diagonals = std::min(deltaX, deltaY);
    int orthoginals = std::abs(deltaX - deltaY);
    return 14 * diagonals + 10 * orthoginals;
}

bool breadthFirst::checkNeighbor(Vec2i& p, int neighborG) {
    std::list<node2>::iterator i;
    i = std::find(open.begin(), open.end(), p);
    if (i != open.end()) {
        if ((*i).g < neighborG) {
            return true;
        }
        else {
            open.erase(i);
            return false;
        }
    }
    return false;
}

void breadthFirst::fillOpen(node2& n) {
    int stepCost;
    int neighborG;
    Vec2i neighbourTile;
    for (int x = 0; x < 8; x++) {
        stepCost = x < 4 ? 14 : 10;
        neighbourTile = n.tile + neighbours[x];
        std::list<node2>::iterator i;
        i = std::find(closed.begin(), closed.end(), neighbourTile);
        if (i == closed.end()) {
            if (map.isWithinBounds(neighbourTile)) {
                if (x >= 4 || validDiagonal(n.tile, neighbours[x])) {
                    neighborG = stepCost + n.g;
                    if (!checkNeighbor(neighbourTile, neighborG)) {
                        node2 m;
                        tilesChecked++;
                        m.tieRating = tilesChecked;
                        m.g = neighborG;
                        m.tile = neighbourTile;
                        m.parent = n.tile;
                        open.push_back(m);
                    }
                }
            }
        }
    }
}



Building* breadthFirst::searchForHouse(const Vec2i& s) {
    clear();
    if (showPathfinding) renderWindow.setFramerateLimit(1000);
    bool pathFound = false;
    node2 n;
    end = Vec2i(-1, -1);
    start = s;
    tilesChecked = 0;
    n.g = 0;
    n.tile = s;
    n.parent = Vec2i(-1, -1);
    n.tieRating = tilesChecked;
    open.push_back(n);

    while (!open.empty()) {
        open.sort();
        node2 n = open.front();
        open.pop_front();
        closed.push_back(n);
        FixedEntity* fixedEntity = em.getEntityFromTile(n.tile);
        if (fixedEntity != nullptr) {
            Building* building = dynamic_cast<Building*> (fixedEntity);
            if (building != nullptr && &building->buildingType() == &house) {
                pathFound = true;
                end = n.tile;
                return building;
            }
        }
        if (map.isPathable(n.tile))
            fillOpen(n);
        if (showPathfinding) {
            graphics.drawSearchDebug2(open, closed, start, end, nullptr);//after each node
            Sleep(25);
        }
            
    }
    if (showPathfinding) renderWindow.setFramerateLimit(targetFPS);
    return nullptr;
}

std::list<Vec2i> breadthFirst::path() {
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(1000);
    }
    std::list<Vec2i> path;
    path.push_front(closed.back().tile);
    Vec2i parent = closed.back().parent;
    for (std::list<node2>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++) {
        if ((*i).tile == parent && !((*i).tile == start)) {
            path.push_front((*i).tile);
            parent = (*i).parent;
            if (showPathfinding) {
                graphics.drawSearchDebug2(open, closed, start, end, &path);
                Sleep(25); //after each path node
            }
        }
    }
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(targetFPS);
    }
    if (map.isPathable(path.back()) == false) {
        path.pop_back();
    }

    return path;
}

void breadthFirst::clear() {
    open.clear();
    closed.clear();
}
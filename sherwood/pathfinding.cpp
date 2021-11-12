#include "pathfinding.h"
#include "globals.h"
#include "graphics.h"
#include <Windows.h>
#include <chrono>

Vec2i neighbours[8] = { 
    Vec2i(-1, -1), Vec2i(1, -1), Vec2i(-1, 1), Vec2i(1, 1),
    Vec2i(0, -1), Vec2i(-1, 0), Vec2i(0, 1), Vec2i(1, 0)
};

bool Pathfinder::orthoginalNeighborIsPathable(const Vec2i tile) {
    Vec2i neighbourTile;
    for (int x = 4; x < 8; x++) {
        neighbourTile = tile + neighbours[x];
        if (map.isWithinBounds(neighbourTile) && tileIsPathable(neighbourTile))
            return true;
    }
    return false;
}

bool Pathfinder::tileIsPathable(const Vec2i _tile) const {
    return (pathableTypes.find(map.terrainGrid[_tile.x][_tile.y]) != pathableTypes.end() &&
        map.getEntityFromTile(_tile) == nullptr);
}

bool Pathfinder::validDiagonal(const Vec2i& source, const Vec2i& direction) const {
    Vec2i tile1(source.x, source.y + direction.y);
    Vec2i tile2(source.x + direction.x, source.y);
    return tileIsPathable(tile1) && tileIsPathable(tile2);
}


AStar::AStar() :
    tilesChecked(0)
{}

int AStar::heuristic(const Vec2i& p) {
    int deltaX = std::abs(end.x - p.x);
    int deltaY = std::abs(end.y - p.y);
    int diagonals = std::min(deltaX, deltaY);
    int orthoginals = std::abs(deltaX - deltaY);
    return 14 * diagonals + 10 * orthoginals;
}

bool AStar::search(const Vec2i& s, const Vec2i& e, std::set<int> _pathableTypes) {
    if (showPathfinding) renderWindow.setFramerateLimit(1000);
    auto begin = std::chrono::high_resolution_clock::now();
    bool pathFound = false;
    pathableTypes = _pathableTypes;
    if (tileIsPathable(e) || orthoginalNeighborIsPathable(e)) {
        clear();
        end = e;
        start = s;
        tilesChecked = 0;
        open.push_back(AStarOpenTuple(0, tilesChecked, start));
        std::push_heap(open.begin(), open.end(), CompareAStarTuple());
        tilesChecked++;
        cameFrom[start] = start;
        costSoFar[start] = 0;

        while (!open.empty()) {
            Vec2i best = std::get<2>(open.front());
            std::pop_heap(open.begin(), open.end(), CompareAStarTuple());
            open.pop_back();
            closed.insert(best);
            if (best == end) {
                pathFound = true;
                break;
            }
            if (tileIsPathable(best)) {
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
                                    std::vector<AStarOpenTuple>::iterator i;
                                    i = std::find_if(open.begin(), open.end(), [&](AStarOpenTuple t) { return std::get<2>(t) == neighbor; });
                                    if (i == open.end()) {
                                        open.push_back(AStarOpenTuple(newCost + heuristic(neighbor), tilesChecked, neighbor));
                                        std::push_heap(open.begin(), open.end(), CompareAStarTuple());
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
                graphics.drawAStar(&best, nullptr);
                //Sleep(20); //after each path node
            }      
        }
    }
    if (showPathfinding) renderWindow.setFramerateLimit(targetFPS);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("AStar %.3f milliseconds\n", elapsed.count() * 1e-6);
    return pathFound;
}

std::list<Vec2i> AStar::path() {
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
            graphics.drawAStar(&current, &path);
            Sleep(10); //after each path node
        }
    }
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(targetFPS);
    }
    if (tileIsPathable(path.back()) == false) {
        path.pop_back();
    }
    return path;
}

void AStar::clear() {
    open.clear();
    closed.clear();
    costSoFar.clear();
    cameFrom.clear();
}

Entity* BreadthFirst::search(const Vec2i& s, const EntityStyle& fet, std::set<int> _pathableTypes) {
   if (showPathfinding) renderWindow.setFramerateLimit(1000);
   pathableTypes = _pathableTypes;
    auto begin = std::chrono::high_resolution_clock::now();
    clear();
    start = s;
    open.push_back(BreadthFirstOpenTuple(0, start));
    std::push_heap(open.begin(), open.end(), CompareBreadthFirstTuple());
    cameFrom[start] = start;
    costSoFar[start] = 0;
    Entity* result = nullptr;
    while (!open.empty()) {
        Vec2i best = std::get<1>(open.front());
        std::pop_heap(open.begin(), open.end(), CompareBreadthFirstTuple());
        open.pop_back();
        closed.insert(best);
        Entity* entity = map.getEntityFromTile(best);
        if (entity != nullptr && &entity->entityStyle() == &fet) {
            end = best;
            result = entity;
            break;
        }
        if (tileIsPathable(best)) {
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
                                std::vector<BreadthFirstOpenTuple>::iterator i;
                                i = std::find_if(open.begin(), open.end(), [&](BreadthFirstOpenTuple t) { return std::get<1>(t) == neighbor; });
                                if (i == open.end()) {
                                    open.push_back(BreadthFirstOpenTuple(newCost, neighbor));
                                    std::push_heap(open.begin(), open.end(), CompareBreadthFirstTuple());
                                }
                                else {
                                    std::get<0>(*i) = newCost;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (showPathfinding) {
            graphics.drawBreadthFirst(nullptr, &best, nullptr);
            //Sleep(20); //after each path node
        }
    }
    if (showPathfinding) renderWindow.setFramerateLimit(targetFPS);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Breadthfirst %.3f milliseconds\n", elapsed.count() * 1e-6);
    return result;
}

std::list<Vec2i> BreadthFirst::path() {
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
            graphics.drawBreadthFirst(&end, &current, &path);
            Sleep(10); //after each path node
        }
    }
    if (showPathfinding) {
        Sleep(100);
        renderWindow.setFramerateLimit(targetFPS);
    }
    if (tileIsPathable(path.back()) == false) {
        path.pop_back();
    }

    return path;
}

void BreadthFirst::clear() {
    open.clear();
    closed.clear();
    costSoFar.clear();
    cameFrom.clear();
}
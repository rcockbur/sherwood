#include "pathfinding.h"
#include "globals.h"

bool node::operator == (const node& o) { return pos == o.pos; }
bool node::operator == (const Vec2i& o) { return pos == o; }
bool node::operator < (const node& o) { return h + g < o.h + o.g; }

aStar::aStar() {
    neighbours[0] = Vec2i(-1, -1); 
    neighbours[1] = Vec2i(1, -1);
    neighbours[2] = Vec2i(-1, 1); 
    neighbours[3] = Vec2i(1, 1);
    neighbours[4] = Vec2i(0, -1); 
    neighbours[5] = Vec2i(-1, 0);
    neighbours[6] = Vec2i(0, 1); 
    neighbours[7] = Vec2i(1, 0);
}
int aStar::calcDist(Vec2i& p) {
    // need a better heuristic
    int x = end.x - p.x;
    int y = end.y - p.y;
    return(10*(sqrt(x * x + y * y)));
}

bool aStar::existVec2i(Vec2i& p, int neighborF) {
    std::list<node>::iterator i;
    i = std::find(closed.begin(), closed.end(), p);
    if (i != closed.end()) {
        if ((*i).g + (*i).h < neighborF) {
            return true;
        }
        else { 
            closed.erase(i); 
            return false; 
        }
    }
    i = std::find(open.begin(), open.end(), p);
    if (i != open.end()) {
        if ((*i).g + (*i).h < neighborF) {
            return true;
        }
        else { 
            open.erase(i); 
            return false; 
        }
    }
    return false;
}

//returns true if a neighbor is the end node
bool aStar::fillOpen(node& n) {
    int stepCost;
    int neighborG;
    int neighborH;
    Vec2i neighbour;

    for (int x = 0; x < 8; x++) {
        stepCost = x < 4 ? 14 : 10; //diagonals have different cost
        neighbour = n.pos + neighbours[x];
        if (neighbour == end) 
            return true;

        if (map.isWithinBounds(neighbour) && map.isPathable(neighbour)) {
            neighborG = stepCost + n.g;
            neighborH = calcDist(neighbour);
            if (!existVec2i(neighbour, neighborG + neighborH)) {
                node m;
                m.g = neighborG;
                m.h = neighborH;
                m.pos = neighbour;
                m.parent = n.pos;
                open.push_back(m);
            }
        }
    }
    return false;
}

bool aStar::search(Vec2i& s, Vec2i& e) {
    node n; 
    end = e; 
    start = s;
    n.g = 0; 
    n.pos = s; 
    n.parent = Vec2i(-1,-1); 
    n.h = calcDist(s);
    open.push_back(n);
    while (!open.empty()) {
        //open.sort();
        node n = open.front();
        open.pop_front();
        closed.push_back(n);
        if (fillOpen(n)) 
            return true;
    }
    return false;
}
int aStar::path(std::list<Vec2i>& path) {
    path.push_front(end);
    int cost = 1 + closed.back().g;
    path.push_front(closed.back().pos);
    Vec2i parent = closed.back().parent;

    for (std::list<node>::reverse_iterator i = closed.rbegin(); i != closed.rend(); i++) {
        if ((*i).pos == parent && !((*i).pos == start)) {
            path.push_front((*i).pos);
            parent = (*i).parent;
        }
    }
    path.push_front(start);
    return cost;
}

void aStar::clear() {
    open.clear();
    closed.clear();
}
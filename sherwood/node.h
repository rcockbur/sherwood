#pragma once
#include "types.h"

class node {
public:
    bool operator == (const node& o);
    bool operator == (const Vec2i& o);
    bool operator < (const node& o);
    Vec2i tile, parent;
    int f;
    int g;
    int h;
    int tieRating;

};
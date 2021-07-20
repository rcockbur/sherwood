#include "node.h"

bool node::operator == (const node& o) { return tile == o.tile; }
bool node::operator == (const Vec2i& o) { return tile == o; }
bool node::operator < (const node& o) { 
	return ((f < o.f) || (f == o.f && tieRating > o.tieRating));
}


bool node2::operator == (const node2& o) { return tile == o.tile; }
bool node2::operator == (const Vec2i& o) { return tile == o; }
bool node2::operator < (const node2& o) {
	return ((g < o.g));
}
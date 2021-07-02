#include "types.h"



std::ostream& operator<< (std::ostream& out, const Vec2i& vec) {
	out << "(" << vec.x << "," << vec.y << ")";
	return out;
}
std::ostream& operator<< (std::ostream& out, const Vec2f& vec) {
	out << "(" << vec.x << "," << vec.y << ")";
	return out;
}
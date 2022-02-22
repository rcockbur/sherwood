#include "types.h"



std::ostream& operator<< (std::ostream& out, const Vec2i& vec) {
	out << vec.x << "," << vec.y;
	return out;
}
std::ostream& operator<< (std::ostream& out, const Vec2f& vec) {
	out << vec.x << "," << vec.y;
	return out;
}

bool CompareAStarTuple::operator()(const AStarOpenTuple& lhs, const AStarOpenTuple& rhs) const {
	return (std::get<0>(lhs) > std::get<0>(rhs) ||
		std::get<0>(lhs) == std::get<0>(rhs) && std::get<1>(lhs) < std::get<1>(rhs));
}

bool CompareBreadthFirstTuple::operator()(const BreadthFirstOpenTuple& lhs, const BreadthFirstOpenTuple& rhs) const {
	return (std::get<0>(lhs) > std::get<0>(rhs));
}

bool CompareVec2i::operator()(const Vec2i& lhs, const Vec2i& rhs) const {
	return (lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y));
}
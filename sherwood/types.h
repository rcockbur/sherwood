#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

template<typename T>
sf::Vector2<T> DivideVec2(const sf::Vector2<T>& left, const sf::Vector2<T>& right) {
	if (right.x == 0 || right.y == 0) throw(std::logic_error("divide by zero"));
	return sf::Vector2<T>(left.x / right.x, left.y / right.y);
}

typedef std::ostringstream oss;
typedef sf::Vector2<float> Vec2f;
typedef sf::Vector2<int> Vec2i;
typedef sf::Vector2<unsigned int> Vec2u;
typedef sf::Color Color;
typedef sf::Rect<float> Rect;

enum ResourceType { food, wood, gold, stone };
enum TerrainType { water, grass };
enum class ActivityStatus { success, failure, inProgress };
enum class CompleteStatus { complete, incomplete };

std::ostream& operator<< (std::ostream& out, const Vec2i& vec);
std::ostream& operator<< (std::ostream& out, const Vec2f& vec);
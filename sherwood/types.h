#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <set>

class Entity;

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
typedef sf::Shape Shape;
typedef sf::Sprite Sprite;
typedef sf::Texture Texture;
typedef sf::CircleShape CircleShape;
typedef sf::RectangleShape RectangleShape;
typedef std::tuple<int, int, Vec2i> AStarOpenTuple;
typedef std::tuple<int, Vec2i> BreadthFirstOpenTuple;
typedef std::unordered_map<int, Entity*> EntityGroup;

enum ResourceType { food, wood, gold, stone };
enum TerrainType { water, grass };
enum class ActivityStatus { success, failure, inProgress };
enum class CompleteStatus { complete, incomplete };
//enum class TargetingMode { none, placeBuilding, editTerrain, entityCommand };

std::ostream& operator<< (std::ostream& out, const Vec2i& vec);
std::ostream& operator<< (std::ostream& out, const Vec2f& vec);

struct CompareAStarTuple {
	bool operator()(const AStarOpenTuple& lhs, const AStarOpenTuple& rhs) const;
};

struct CompareBreadthFirstTuple {
	bool operator()(const BreadthFirstOpenTuple& lhs, const BreadthFirstOpenTuple& rhs) const;
};

struct CompareVec2i {
	bool operator()(const Vec2i& lhs, const Vec2i& rhs) const;
};

typedef std::map<Vec2i, int, CompareVec2i> TileIntMap;
typedef std::map<Vec2i, Vec2i, CompareVec2i> TileTileMap;
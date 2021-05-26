#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Entity;

typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2u Vec2u;
typedef sf::Color Color;
typedef unsigned int uint;
typedef sf::Rect<float> Rect;

enum class ET{ DEER };
constexpr uint ENTITY_TYPES = 1;
enum class AT{ MOVE };

std::ostream& operator<< (std::ostream& out, const Vec2i& vec);
std::ostream& operator<< (std::ostream& out, const Vec2f& vec);
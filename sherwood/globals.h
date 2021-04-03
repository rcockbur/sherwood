#pragma once

#include <SFML/System/Vector2.hpp>

typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2i;
typedef unsigned int uint;

enum class ET{ DEER };
constexpr uint ENTITY_TYPES = 1;
enum class AT{ MOVE };

void initGlobals();
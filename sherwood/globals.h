#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2u Vec2u;
typedef unsigned int uint;

enum class ET{ DEER };
constexpr uint ENTITY_TYPES = 1;
enum class AT{ MOVE };

struct Colors {
	sf::Color blue = sf::Color::Blue;
	sf::Color black = sf::Color::Black;
	sf::Color green = sf::Color::Green;
	sf::Color red = sf::Color::Red;
	sf::Color white = sf::Color::White;
	sf::Color yellow = sf::Color::Yellow;
	sf::Color grey = sf::Color(100, 100, 100);
	sf::Color transparent = sf::Color(0, 0, 0, 0);
};


void initGlobals();
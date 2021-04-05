#pragma once
#include <SFML/Graphics.hpp>

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

extern Colors colors;
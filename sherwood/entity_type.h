#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "globals.h"

struct EntityType {
	ET id;
	std::string name;
	sf::Color color;
	uint movePeriod;
	EntityType(ET, std::string, sf::Color, uint _movePeriod);
};
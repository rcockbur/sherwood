#pragma once
#include "types.h"

class EntityType {
public:
	ET id;
	std::string name;
	sf::Color color;
	uint movePeriod;
	float moveDistance;
	EntityType(ET, std::string, sf::Color, uint _movePeriod, float _moveDistance);
};
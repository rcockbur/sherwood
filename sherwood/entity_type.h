#pragma once
#include "types.h"

class EntityType {
public:
	//ET id;
	std::string name;
	sf::Color color;
	EntityType(std::string, sf::Color);
};

class UnitType : public EntityType {
public:
	uint movePeriod;
	float moveDistance;
	UnitType(std::string, sf::Color, uint _movePeriod, float _moveDistance);
};
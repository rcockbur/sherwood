#pragma once
#include "types.h"

class EntityType {
public:
	const std::string name;
	const sf::Color color;
	EntityType(const std::string, const sf::Color);
};

class UnitType : public EntityType {
public:
	const uint movePeriod;
	const float moveDistance;
	UnitType(std::string, sf::Color, uint _movePeriod, float _moveDistance);
};


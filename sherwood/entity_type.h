#pragma once
#include "types.h"
#include "resource.h"

class EntityType {
public:
	const std::string name;
	const sf::Color color;	
	Resources resources;
	EntityType(const std::string, const sf::Color);
};

class UnitType : public EntityType {
public:
	const int movePeriod;
	const float moveDistance;
	UnitType(const std::string, const sf::Color, int _movePeriod, float _moveDistance);
};

class BuildingType : public EntityType {
public:
	BuildingType(const std::string, const sf::Color);
};

class DepositType : public EntityType {
public:
	DepositType(const std::string name, const sf::Color color, const int resourceType,
		const int amount);
};
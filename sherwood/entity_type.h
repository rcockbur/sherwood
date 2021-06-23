#pragma once
#include "types.h"
#include "resource.h"

class EntityType {
public:
	const std::string name;
	const sf::Color color;	
	EntityType(const std::string, const sf::Color);
};

class DoodadType: public EntityType {
public:
	DoodadType(const std::string, const sf::Color);
};

class DepositType : public EntityType {
public:
	const int resourceType;
	int amount;
	DepositType(const std::string name, const sf::Color color, const int resourceType,
		const int amount);
};

class ComplexEntityType : public EntityType {
public:
	Resources resources;
	ComplexEntityType(const std::string, const sf::Color);
};

class UnitType : public ComplexEntityType {
public:
	const int movePeriod;
	const float moveDistance;
	UnitType(const std::string, const sf::Color, int _movePeriod, float _moveDistance);
};

class BuildingType : public ComplexEntityType {
public:
	BuildingType(const std::string, const sf::Color);
};


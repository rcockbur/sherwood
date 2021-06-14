#pragma once
#include "types.h"

class ResourceType;

class EntityType {
public:
	const std::string name;
	const sf::Color color;
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
	const ResourceType& resourceType;
	int amount;
	DepositType(const std::string name, const sf::Color color, const ResourceType& resourceType,
		const int amount);
};
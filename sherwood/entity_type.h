#pragma once
#include "types.h"
#include "resources.h"

class EntityType {
public:
	std::string name;
	sf::Color color;	

	EntityType(std::string&&);
};

class FixedEntityType : public EntityType {
public:
	FixedEntityType(std::string&& _name);
};

class DoodadType: public FixedEntityType {
public:
	DoodadType(std::string&& _name);
};

class DepositType : public FixedEntityType {
public:
	int resourceType;
	int amount;

	DepositType(std::string&& _name);
};

class BuildingType : public FixedEntityType {
public:
	Resources resources;

	BuildingType(std::string&& _name);
};

class UnitType : public EntityType {
public:
	int movePeriod;
	float moveDistance;
	int carryCapacity;
	int gatherPeriod;

	UnitType(std::string&& _name);
};




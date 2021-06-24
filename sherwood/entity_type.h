#pragma once
#include "types.h"
#include "resources.h"

class EntityType {
public:
	std::string name;
	sf::Color color;	
	EntityType(std::string&&);
};

class DoodadType: public EntityType {
public:
	DoodadType(std::string&& _name);
};

class DepositType : public EntityType {
public:
	int resourceType;
	int amount;
	DepositType(std::string&& _name);
};

class ComplexEntityType : public EntityType {
public:
	ComplexEntityType(std::string&& _name);
};

class UnitType : public ComplexEntityType {
public:
	int movePeriod;
	float moveDistance;
	int carryCapacity;
	int gatherPeriod;
	UnitType(std::string&& _name);
};

class BuildingType : public ComplexEntityType {
public:
	Resources resources;
	BuildingType(std::string&& _name);
};


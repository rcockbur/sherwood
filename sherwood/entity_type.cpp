#include "entity_type.h"
#include "types.h"

EntityType::EntityType(std::string&& _name) : 
	name(std::move(_name))
{}

DoodadType::DoodadType(std::string&& _name) :
	EntityType(std::move(_name))
{}

DepositType::DepositType(std::string&& _name) :
	EntityType(std::move(_name)),
	resourceType(0),
	amount(0)
{}

ComplexEntityType::ComplexEntityType(std::string&& _name) :
	EntityType(std::move(_name))
{}

UnitType::UnitType(std::string&& _name) :
	ComplexEntityType(std::move(_name)),
	movePeriod(0),
	moveDistance(0.0f),
	carryCapacity(0),
	gatherPeriod(0)
{}

BuildingType::BuildingType(std::string&& _name) :
	ComplexEntityType(std::move(_name))
{}


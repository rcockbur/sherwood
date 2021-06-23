#include "entity_type.h"
#include "types.h"

EntityType::EntityType(const std::string _name, const sf::Color _color) : 
	name(_name), 
	color(_color)
{}

DoodadType::DoodadType(const std::string _name, const sf::Color _color) :
	EntityType(_name, _color)
{}

DepositType::DepositType(const std::string name, const sf::Color color, const int _resourceType,
	const int _amount) :
	EntityType(name, color),
	resourceType(_resourceType),
	amount(_amount)

{}

ComplexEntityType::ComplexEntityType(const std::string name, const sf::Color color) :
	EntityType(name, color)
{}

UnitType::UnitType(const std::string name, const sf::Color color, int movePeriod, float moveDistance) :
	ComplexEntityType(name, color),
	movePeriod(movePeriod),
	moveDistance(moveDistance) 
{
	resources[food] = 50;
	resources[wood] = 100;
}

BuildingType::BuildingType(const std::string name, const sf::Color color) :
	ComplexEntityType(name, color)
{}


#include "entity_type.h"
#include "types.h"

EntityType::EntityType(const std::string _name, const sf::Color _color) : 
	name(_name), 
	color(_color)
{

}

UnitType::UnitType(const std::string name, const sf::Color color, int movePeriod, float moveDistance) :
	EntityType(name, color),
	movePeriod(movePeriod),
	moveDistance(moveDistance) 
{
	resources[food] = 50;
	resources[wood] = 100;
}

BuildingType::BuildingType(const std::string name, const sf::Color color) :
	EntityType(name, color)
{

}

DepositType::DepositType(const std::string name, const sf::Color color, const int resourceType, 
	const int amount) :
	EntityType(name, color)
{
	resources[resourceType] = amount;
}
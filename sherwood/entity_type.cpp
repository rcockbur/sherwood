#include "entity_type.h"

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

}

BuildingType::BuildingType(const std::string name, const sf::Color color) :
	EntityType(name, color)
{

}

DepositType::DepositType(const std::string name, const sf::Color color, const ResourceType& _resourceType, 
	const int _amount) :
	EntityType(name, color),
	resourceType(_resourceType),
	amount(_amount)
{

}
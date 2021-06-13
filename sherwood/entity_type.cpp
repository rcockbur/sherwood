#include "entity_type.h"

EntityType::EntityType(const std::string _name, const sf::Color _color) : 
	name(_name), 
	color(_color)
{

}

UnitType::UnitType(std::string name, sf::Color color, uint movePeriod, float moveDistance) :
	EntityType(name, color),
	movePeriod(movePeriod),
	moveDistance(moveDistance) 
{

}


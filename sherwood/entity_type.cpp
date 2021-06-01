#include "entity_type.h"

EntityType::EntityType(std::string _name, sf::Color _color) : 
	//id(_id), 
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
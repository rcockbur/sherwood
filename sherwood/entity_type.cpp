#include "entity_type.h"

EntityType::EntityType(ET _id, std::string _name, sf::Color _color) : 
	id(_id), 
	name(_name), 
	color(_color)
{

}

UnitType::UnitType(ET id, std::string name, sf::Color color, uint movePeriod, float moveDistance) :
	EntityType(id, name, color),
	movePeriod(movePeriod),
	moveDistance(moveDistance) 
{

}
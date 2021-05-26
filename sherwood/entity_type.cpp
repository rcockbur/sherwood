#include "entity_type.h"

EntityType::EntityType(ET _id, std::string _name, sf::Color _color, uint _movePeriod, float _moveDistance) : 
	id(_id), 
	name(_name), 
	color(_color), 
	movePeriod(_movePeriod), 
	moveDistance(_moveDistance)
{

}
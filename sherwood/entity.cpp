#include "globals.h"
#include "entity.h"

Entity::Entity(EntityType* _type, uint _id, const Vec2i& _tile)
	: type(_type), id(_id), tile(_tile), color(NULL) 
{
}

void Entity::update()
{
	if (abilityQueue.size() > 0) {
		Ability* ability = abilityQueue.front();
		bool isComplete = ability->execute();
		if (isComplete)
			abilityQueue.pop_back();
	}
}

void Entity::addAbility(Ability* ability) {
	abilityQueue.push_back(ability);
}
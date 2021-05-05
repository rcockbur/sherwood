#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_type.h"

Entity::Entity(Map& _map, EntityType& _type, uint _id, const Vec2i& _tile): 
	map(_map), 
	type(_type), 
	id(_id), 
	tile(_tile), 
	color(NULL),
	canMoveAt(0)
{
	map.entityGrid[tile.x][tile.y] = this;
}

void Entity::update()
{
	if (abilityQueue.size() > 0) {
		Ability* ability = abilityQueue.front();
		bool isComplete = ability->execute();
		if (isComplete)
			abilityQueue.pop_front();
	}
}

void Entity::addAbility(Ability* ability) 
{
	abilityQueue.push_back(ability);
}

void Entity::move(const Vec2i _tile)
{
	map.entityGrid[tile.x][tile.y] = nullptr;
	tile = _tile;
	map.entityGrid[tile.x][tile.y] = this;
}
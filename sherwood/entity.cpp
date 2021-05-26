#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_type.h"
#include "globals.h"

Entity::Entity(Map& _map, EntityType& _type, uint _id, const Vec2i& _tile): 
	map(_map), 
	type(_type), 
	id(_id), 
	tile(_tile), 
	position(wm.tileToWorld(_tile)),
	bounds(calculateBounds(position)),
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

void Entity::setAbility(Ability* ability)
{
	abilityQueue.clear();
	abilityQueue.push_back(ability);
}

bool Entity::moveTowards(const Vec2i& targetTile)
{
	if (tile != targetTile) {
		map.entityGrid[tile.x][tile.y] = nullptr;
		tile = targetTile;
		map.entityGrid[tile.x][tile.y] = this;
	}
	Vec2f targetPos = wm.tileToWorld(targetTile);
	Vec2f diff = targetPos - position;
	float dist = (float)sqrt(pow(diff.x, 2) + pow(diff.y, 2));
	if (dist > type.moveDistance) {
		(diff /= dist) *= type.moveDistance;
		position += diff;
		bounds = calculateBounds(position);
		return false;
	}
	else {
		position = targetPos;
		bounds = calculateBounds(position);
		return true;
	}

}

Rect Entity::calculateBounds(const Vec2f& pos) {
	return Rect(pos.x - wm.tileSize.x / 2, pos.y - wm.tileSize.y / 2, wm.tileSize.x, wm.tileSize.y);
}
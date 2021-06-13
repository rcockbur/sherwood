#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_type.h"
#include "pathfinding.h"
#include "globals.h"
#include "utility.h"

Entity::Entity(const EntityType& type, uint id, const Vec2i& tile) :
	type(type),
	id(id),
	position(tileToWorld(tile)),
	bounds(calculateBounds(position)),
	color(NULL),
	isSelected(false)
{
}

void Entity::update() {
}

Rect Entity::calculateBounds(const Vec2f& pos) {
	return Rect(pos.x - ENTITY_SIZE / 2, pos.y - ENTITY_SIZE / 2, ENTITY_SIZE, ENTITY_SIZE);
}

Unit::Unit(const UnitType& _type, uint _id, const Vec2i& _tile) :
	Entity(_type, _id, _tile),
	type(_type),
	canMoveAt(0)
{
}

void Unit::update()
{
	if (abilityQueue.size() > 0) {
		Ability* ability = abilityQueue.front();
		bool isComplete = ability->execute();
		if (isComplete) {
			delete ability;
			abilityQueue.pop_front();
		}	
	}
}

void Unit::addAbility(Ability* ability)
{
	abilityQueue.push_back(ability);
}

void Unit::setAbility(Ability* ability)
{
	abilityQueue.clear();
	abilityQueue.push_back(ability);
}

bool Unit::moveTowards(const Vec2i& targetTile)
{
	Vec2f targetPos = tileToWorld(targetTile);
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

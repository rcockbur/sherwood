#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_type.h"
#include "pathfinding.h"
#include "globals.h"

Entity::Entity(EntityType& _type, uint _id, const Vec2i& _tile):
	type(_type), 
	id(_id), 
	tile(_tile), 
	position(wm.tileToWorld(_tile)),
	bounds(calculateBounds(position)),
	color(NULL)
{
	map.entityGrid[tile.x][tile.y] = this;
}

void Entity::update()
{
}

void Entity::targetTile(const Vec2i& tile) {
	std::cout << "Entity targetTile\n";
}

Rect Entity::calculateBounds(const Vec2f& pos) {
	return Rect(pos.x - ENTITY_SIZE.x / 2, pos.y - ENTITY_SIZE.y / 2, ENTITY_SIZE.x, ENTITY_SIZE.y);
}






Unit::Unit(UnitType& _type, uint _id, const Vec2i& _tile) :
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
		if (isComplete)
			abilityQueue.pop_front();
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

void Unit::targetTile(const Vec2i& tile) {
	astar.clear();
	if (astar.search(selectedEntity->tile, tile)) {
		std::list<Vec2i> path;
		int c = astar.path(path);
		Move* move = new Move(*this, path);
		setAbility(move);
	}
	std::cout << "Unit targetTile\n";
}
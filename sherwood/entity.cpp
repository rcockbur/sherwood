#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_type.h"
#include "pathfinding.h"
#include "globals.h"
#include "utility.h"
#include "string"

int Entity::id_index = 0;

Entity::Entity(const EntityType& type, const Vec2i tile) :
	type(type),
	id(id_index),
	position(tileToWorld(tile)),
	bounds(calculateBounds(position)),
	color(type.color),
	isSelected(false),
	resources(type.resources)
	
{
	++id_index;
}

void Entity::update() {
}

std::ostringstream Entity::getSelectionText() {
	std::ostringstream s;
	s << "Type: " << type.name << "\n";
	s << "ID: " << id << "\n";
	//s << "Pos: " << (Vec2i)(position) << "\n";
	s << "Tile: " << worldToTile(position) << "\n";
	for (int resourceType = 0; resourceType < NUM_RESOURCES; resourceType++) {
		if (resources[resourceType] > 0) {
			s << "resource: " << resources[resourceType] << " " << resourceNames[resourceType] << "\n";
		}
	}
	return s;
}

Rect Entity::calculateBounds(const Vec2f& pos) {
	return Rect(pos.x - ENTITY_SIZE / 2, pos.y - ENTITY_SIZE / 2, ENTITY_SIZE, ENTITY_SIZE);
}

Unit::Unit(const UnitType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type),
	canMoveAt(0),
	home(nullptr)
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

std::ostringstream Unit::getSelectionText() {
	std::ostringstream s = Entity::getSelectionText();
	s << "Home: " << ((home) ? std::to_string(home->id) : "-") << "\n";
	return s;
}

void Unit::addAbility(Ability* ability) {
	abilityQueue.push_back(ability);
}

void Unit::setAbility(Ability* ability) {
	abilityQueue.clear();
	abilityQueue.push_back(ability);
}

void Unit::setHome(Building* _home) {
	home = _home;
}

bool Unit::moveTowards(const Vec2i targetTile) {
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

Building::Building(const BuildingType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type)
{
}

Deposit::Deposit(const DepositType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type)
{
}

std::ostringstream Deposit::getSelectionText() {
	std::ostringstream s = Entity::getSelectionText();
	return s;
}
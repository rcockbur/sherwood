#pragma once
#include "globals.h"
#include <deque>

class Map;
class Ability;
class EntityType;

class Entity {
public:
	const uint id;
	const EntityType& type;
	Vec2i tile;
	sf::Color color;
	std::deque<Ability*> abilityQueue;
	uint canMoveAt;

	Entity(Map& map, EntityType& _type, uint _id, const Vec2i& _tile);
	void update();
	void addAbility(Ability* ability);
	void move(const Vec2i tile);
private:
	Map& map;
};


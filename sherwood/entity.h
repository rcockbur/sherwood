#pragma once
#include "types.h"
#include <deque>

class Map;
class Ability;
class EntityType;

class Entity {
public:
	const uint id;
	const EntityType& type;
	Vec2i tile;
	Vec2f position;
	Rect bounds;
	sf::Color color;
	std::deque<Ability*> abilityQueue;
	uint canMoveAt;
	bool isSelected;

	Entity(Map& map, EntityType& _type, uint _id, const Vec2i& _tile);
	void update();
	void addAbility(Ability* ability);
	void setAbility(Ability* ability);
	bool moveTowards(const Vec2i& targetTile);
private:
	Map& map;
	Rect calculateBounds(const Vec2f& pos);
};


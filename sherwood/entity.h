#pragma once
#include "types.h"
#include <deque>

class Ability;
class EntityType;
class UnitType;
class DoodadType;

class Entity {
public:
	const uint id;
	const EntityType& type;
	Vec2f position;
	Rect bounds;
	sf::Color color;
	bool isSelected;

	Entity(const EntityType& type, uint id, const Vec2i& tile);
	virtual void update();
protected:
	Rect calculateBounds(const Vec2f& pos);
};

class Unit : public Entity {
public:
	const UnitType& type;
	std::deque<Ability*> abilityQueue;
	int canMoveAt;

	Unit(const UnitType& _type, uint _id, const Vec2i& _tile);
	void update();
	void addAbility(Ability* ability);
	void setAbility(Ability* ability);
	bool moveTowards(const Vec2i& targetTile);
};

class Building : public Entity {
public:

};
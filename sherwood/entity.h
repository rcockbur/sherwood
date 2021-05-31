#pragma once
#include "types.h"
#include <deque>

class Ability;
class EntityType;
class UnitType;

class Entity {
public:
	const uint id;
	const EntityType& type;
	Vec2i tile;
	Vec2f position;
	Rect bounds;
	sf::Color color;
	bool isSelected;

	Entity(EntityType& _type, uint _id, const Vec2i& _tile);
	virtual void update();
	virtual void targetTile(const Vec2i& tile);
protected:
	Rect calculateBounds(const Vec2f& pos);
};

class Unit : public Entity {
public:
	const UnitType& type;
	std::deque<Ability*> abilityQueue;
	uint canMoveAt;

	Unit(UnitType& _type, uint _id, const Vec2i& _tile);
	void update();
	void addAbility(Ability* ability);
	void setAbility(Ability* ability);
	bool moveTowards(const Vec2i& targetTile);
	virtual void targetTile(const Vec2i& tile);
};

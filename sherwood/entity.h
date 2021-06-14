#pragma once
#include "types.h"
#include <sstream>
#include <deque>
#include "resource.h"

class Ability;
class EntityType;
class UnitType;
class BuildingType;
class DepositType;
class DoodadType;
class Building;

class Entity {
public:
	static int id_index;
	const int id;
	const EntityType& type;
	Vec2f position;
	Rect bounds;
	sf::Color color;
	bool isSelected;

	Entity(const EntityType& type, const Vec2i tile);
	virtual void update();
	virtual std::ostringstream getSelectionText();
protected:
	Rect calculateBounds(const Vec2f& pos);
};

class Unit : public Entity {
public:
	const UnitType& type;
	std::deque<Ability*> abilityQueue;
	int canMoveAt;
	Building* home;
	Unit(const UnitType& type, const Vec2i tile);
	void update();
	std::ostringstream getSelectionText();
	void addAbility(Ability* ability);
	void setAbility(Ability* ability);
	void setHome(Building* home);
	bool moveTowards(const Vec2i targetTile);
};

class Building : public Entity {
public:
	const BuildingType& type;
	Building(const BuildingType& type, const Vec2i tile);
};

class Deposit : public Entity {
public:
	const DepositType& type;
	const Resource resource;
	Deposit(const DepositType& type, const Vec2i tile);
	std::ostringstream getSelectionText();
};
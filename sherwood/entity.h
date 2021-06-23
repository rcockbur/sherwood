#pragma once
#include "types.h"
#include <sstream>
#include <deque>
#include "resource.h"

class Ability;
class EntityType;
class DoodadType;
class ComplexEntityType;
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
	virtual void getSelectionText(std::ostringstream&);
protected:
	Rect calculateBounds(const Vec2f& pos);
};

class Doodad : public Entity {
public:
	const DoodadType& type;
	Doodad(const DoodadType&, const Vec2i tile);
};

class Deposit : public Entity {
public:
	const DepositType& type;
	int amount;
	Deposit(const DepositType& type, const Vec2i tile);
	void getSelectionText(std::ostringstream&);
};

class ComplexEntity : public Entity {
public:
	const ComplexEntityType& type;
	Resources resources;
	ComplexEntity(const ComplexEntityType&, const Vec2i tile);
	virtual void getSelectionText(std::ostringstream&);
};

class Unit : public ComplexEntity {
public:
	const UnitType& type;
	std::deque<Ability*> abilityQueue;
	int canMoveAt;
	Building* home;
	Unit(const UnitType& type, const Vec2i tile);
	void update();
	void getSelectionText(std::ostringstream&);
	void addAbility(Ability* ability);
	void setAbility(Ability* ability);
	void setHome(Building* home);
	bool moveTowards(const Vec2i targetTile);
};

class Building : public ComplexEntity {
public:
	const BuildingType& type;
	Building(const BuildingType& type, const Vec2i tile);
};


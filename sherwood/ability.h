#pragma once
#include "types.h"
#include <list>
#include "lookup.h"

class Unit;

class Ability {
public:
	virtual ActivityStatus execute() = 0;
};

class Move : public Ability {
public:
	Move(Unit& unit, Vec2i dest, std::list<Vec2i>&& path);
	ActivityStatus execute();
protected:
	Unit& unit;
	const Vec2i dest;
	std::list<Vec2i> path;
	void followPath();
};

class Harvest : public Move {
public:
	Harvest(Unit& unit, Lookup depositLookup, std::list<Vec2i>&& path);
	ActivityStatus execute();
private:
	const Lookup depositLookup;
	bool hasStartedHarvesting;
};

class ReturnResources : public Move {
public :
	ReturnResources(Unit& unit, Lookup buildingLookup, std::list<Vec2i>&& path);
	ActivityStatus execute();
private:
	const Lookup houseLookup;
};
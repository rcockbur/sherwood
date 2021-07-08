#pragma once
#include "types.h"
#include <list>
#include "lookup.h"

class Unit;

class Ability {
public:
	virtual ActivityStatus start() = 0;
	virtual ActivityStatus execute() = 0;
};

class Move : public Ability {
public:
	Move(Unit& unit, Vec2i dest);
	ActivityStatus start();
	ActivityStatus execute();
protected:
	Unit& unit;
	const Vec2i dest;
	std::list<Vec2i> path;
	bool hasStarted;
	void followPath();
};

class Harvest : public Move {
public:
	Harvest(Unit& unit, Lookup depositLookup);
	ActivityStatus start();
	ActivityStatus execute();
private:
	const Lookup depositLookup;
	bool hasStartedHarvesting;
};

class ReturnResources : public Move {
public :
	ReturnResources(Unit& unit, Lookup buildingLookup);
	ActivityStatus execute();
};
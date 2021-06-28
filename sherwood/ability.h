#pragma once
#include "types.h"
#include <list>
#include "entity.h"
#include "resources.h"
#include "lookup.h"


class Ability {
public:
	virtual ActivityStatus start() = 0;
	virtual ActivityStatus execute() = 0;
};

class Move : public Ability {
public:
	Unit& unit;
	const Vec2i dest;
	std::list<Vec2i> path;
	bool hasStarted;
	Move(Unit& unit, const Vec2i dest);
	ActivityStatus start();
	ActivityStatus execute();
protected:
	void followPath();
};

class Harvest : public Move {
public:
	const Lookup depositLookup;
	bool hasStartedHarvesting;
	Harvest(Unit& unit, const Lookup depositLookup);
	ActivityStatus start();
	ActivityStatus execute();
};

class ReturnResources : public Move {
public :
	ReturnResources(Unit& unit, const Lookup buildingLookup);
	ActivityStatus execute();
};
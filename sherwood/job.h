#pragma once
#include "entity.h"
#include "lookup.h"
#include "types.h"

class Ability;

class Job {
public:
	Unit& unit;
	Job(Unit& unit);
	~Job();
	bool hasStarted;
	Ability* ability;
	void setAbility(Ability* ability);
	void destroyAbility();
	CompleteStatus execute();
	ActivityStatus start();
	virtual void checkForAnotherAbility() = 0;
};

class Harvester : public Job {
public:
	const Lookup depositLookup;
	bool forcedHarvest;

	Harvester(Unit&, const Lookup depositLookup);
	void checkForAnotherAbility();
};

class Mover : public Job {
public:
	const Vec2i targetTile;

	Mover(Unit&, const Vec2i targetTile);
	void checkForAnotherAbility();
};
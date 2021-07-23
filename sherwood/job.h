#pragma once
#include "entity.h"
#include "lookup.h"
#include "types.h"
#include <memory>

class Ability;

class Job {
public:
	Unit& unit;
	Job(Unit& unit);
	bool hasStarted;
	std::unique_ptr<Ability> ability;

	CompleteStatus execute();
	ActivityStatus start();
	virtual void checkForAnotherAbility() = 0;
};

class Harvester : public Job {
public:
	const Lookup depositLookup;
	bool forcedHarvest;

	Harvester(Unit&, const Lookup depositLookup);
	void checkForAnotherAbility() override;
};

class Mover : public Job {
public:
	const Vec2i targetTile;

	Mover(Unit&, const Vec2i targetTile);
	void checkForAnotherAbility() override;
};
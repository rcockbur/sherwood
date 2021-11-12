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

	CompleteStatus execute(bool isLastJob);
	ActivityStatus start();
	virtual void checkForAnotherAbility() = 0;
};

class Harvester : public Job {
public:
	Lookup depositLookup;
	bool forcedHarvest;
	const FixedStyle& depositEntityStyle;
	Harvester(Unit&, Deposit& deposit);
	void checkForAnotherAbility() override;
};

class Mover : public Job {
public:
	const Vec2i targetTile;

	Mover(Unit&, const Vec2i targetTile);
	void checkForAnotherAbility() override;
};

class Idler : public Job {
public:
	Idler(Unit&);
	void checkForAnotherAbility() override;
private:
	int idleSince;
};
#pragma once
#include "entity.h"
#include "lookup.h"
#include "types.h"
#include <memory>

class Ability;

class Job {
public:
	Entity& unit;
	Job(Entity& unit);
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
	const EntityStyle& depositEntityStyle;
	Harvester(Entity&, Entity& deposit);
	void checkForAnotherAbility() override;
};

class Mover : public Job {
public:
	const Vec2i targetTile;

	Mover(Entity&, const Vec2i targetTile);
	void checkForAnotherAbility() override;
};

class Garrisoner : public Job {
public:
	Lookup targetLookup;
	Garrisoner(Entity&, Entity& target);
	void checkForAnotherAbility() override;
};
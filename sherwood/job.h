#pragma once
#include "entity.h"
#include "lookup.h"

class Job {
public:
	Unit& unit;
	Job(Unit& unit);
	virtual Status addAbility() = 0;
};

class Harvester : public Job {
public:
	const Lookup depositLookup;
	bool forcedHarvest;
	Harvester(Unit&, const Lookup depositLookup);
	Status addAbility();
};
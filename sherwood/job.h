#pragma once
#include "entity.h"

class Job {
public:
	Unit& unit;
	Job(Unit& unit);
	virtual bool addAbility() = 0;
};

class Harvester : public Job {
public:
	//Deposit& deposit;
	int depositID;
	Harvester(Unit&, Deposit&);
	bool addAbility();
};
#pragma once
#include "types.h"
#include <list>
#include "entity.h"
#include "resources.h"


class Ability {
public:
	virtual bool execute() = 0;
};

class Move : public Ability {
public:
	std::list<Vec2i> path;
	Unit& unit;

	Move(Unit& unit, std::list<Vec2i> path);
	
	bool execute();
protected:
	void followPath();
};

class Harvest : public Move {
public:
	//Deposit& deposit;
	int depositID;
	bool hasReachedDeposit;
	Harvest(Unit& unit, std::list<Vec2i> path, Deposit& source);
	bool execute();
};

class ReturnResources : public Move {
public :
	ReturnResources(Unit& unit, std::list<Vec2i> path);
	bool execute();
};
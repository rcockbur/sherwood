#pragma once
#include "types.h"
#include <list>
#include "entity.h"
#include "resource.h"


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

class Harvest : Move {
public:
	const Deposit& source;
	const int resourceType;
	Harvest(Unit& unit, std::list<Vec2i> path, Deposit& source, int resourceType);
	bool execute();
};
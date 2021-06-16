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
};

class HarvestResource : Move {
public:
	const Deposit& source;
	HarvestResource(Unit& unit, std::list<Vec2i> path, Deposit& source);
};
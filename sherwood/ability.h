#pragma once
#include "types.h"
#include <list>

class Unit;

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
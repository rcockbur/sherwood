#pragma once
#include "globals.h"
#include <list>

class Entity;

class Ability {
public:
	virtual bool execute() = 0;
};

class Move : public Ability {
public:
	std::list<Vec2i> path;
	Entity& entity;

	Move(Entity& entity, std::list<Vec2i> path);
	bool execute();
};
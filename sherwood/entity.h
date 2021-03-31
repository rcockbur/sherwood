#pragma once
#include "component.h"
#include "typedefs.h"

struct Entity {
	unsigned int id;
	Position* position;
	Actor* actor;
	Entity(unsigned int);
};


#pragma once
#include "types.h"
#include <set>
#include "entity.h"
#include "lookup.h"

class EntityManager {
public:
	EntityManager();
	void updateEntities();
	Unit* getUnitByID(const int id) const;
	EntityGroup entities;
	FixedGroup houses;
	UnitGroup units;
};


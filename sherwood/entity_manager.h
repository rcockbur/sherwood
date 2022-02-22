#pragma once
#include "types.h"
#include <set>
#include "entity.h"
#include "lookup.h"

class EntityManager {
public:
	EntityManager();
	void updateEntities();
	Entity* getUnitByID(const int id) const;
	EntityGroup all_entities;
	EntityGroup all_houses;
	EntityGroup all_units;
};


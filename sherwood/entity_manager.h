#pragma once
#include "types.h"
#include <unordered_map>
#include <set>
#include "entity.h"
#include "lookup.h"

class EntityManager {
public:
	EntityManager();
	void updateEntities();
	Unit* getUnitByID(const int id) const;
	std::unordered_map<int, Entity*> entities;
	std::unordered_map<int, Building*> houses;
	std::unordered_map<int, Unit*> units;
};


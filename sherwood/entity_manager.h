#pragma once
#include <vector>
#include "typedefs.h"
#include "entity.h"

class EntityManager {
public:
	Entity* createEntity(Position);
private:
	unsigned int id_index;
	std::vector<Entity*> entities;
};
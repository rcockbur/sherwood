#pragma once
#include <list>
#include <vector>
#include "globals.h"
#include "entity.h"
#include "entity_type.h"

class EntityManager {
public:
	EntityManager();
	EntityType* createEntityType(ET, std::string, sf::Color);
	Entity* createEntity(ET, Vec2i);
	void updateEntities();
private:
	unsigned int entityIndex;
	std::list<Entity> entities;
	std::map<ET, EntityType> entityTypes;
};
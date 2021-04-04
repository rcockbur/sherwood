#pragma once
#include <list>
#include <vector>
#include "globals.h"
#include "entity.h"
#include "entity_type.h"

void initEntities();

class EntityManager {
public:
	EntityManager();
	void createEntityType(ET, std::string, sf::Color, uint);
	Entity* createEntity(ET, Vec2i);
	void updateEntities();
	std::list<Entity*> getEntities();
private:
	uint entityIndex;
	std::map<ET, EntityType*> entityTypes;
	std::list<Entity*> entities;
};
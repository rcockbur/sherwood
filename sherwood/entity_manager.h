#pragma once
#include "types.h"
#include <list>

class EntityType;
class Map;
class Entity;

class EntityManager {
public:
	EntityManager();
	void createEntityType(ET, std::string, sf::Color, uint);
	Entity* createEntity(ET, Vec2i);
	void updateEntities();
	void selectEntity(Entity*);
private:
	uint entityIndex;
	std::map<ET, EntityType*> entityTypes;
	std::list<Entity*> entities;
};
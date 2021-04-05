#pragma once
#include "globals.h"
#include <list>

class EntityType;
class Map;
class Entity;

class EntityManager {
public:
	EntityManager(Map& map);
	void createEntityType(ET, std::string, sf::Color, uint);
	Entity* createEntity(ET, Vec2i);
	void updateEntities();
private:
	Map& map;
	uint entityIndex;
	std::map<ET, EntityType*> entityTypes;
	std::list<Entity*> entities;
};
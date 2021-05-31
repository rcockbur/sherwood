#pragma once
#include "types.h"
#include <list>

class EntityType;
class Map;
class Entity;
class Unit;

class EntityManager {
public:
	EntityManager();
	void createEntityType(ET, std::string, sf::Color);
	void createUnitType(ET, std::string, sf::Color, uint, float);
	Entity* createEntity(ET, Vec2i);
	Unit* createUnit(ET, Vec2i);
	void updateEntities();
	void selectEntity(Entity*);
	std::list<Entity*> entities;
private:
	uint entityIndex;
	std::map<ET, EntityType*> entityTypes;
	
};
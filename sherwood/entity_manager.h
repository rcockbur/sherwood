#pragma once
#include "types.h"
#include <list>

class EntityType;
class UnitType;
class Map;
class Entity;
class Unit;

class EntityManager {
public:
	EntityManager();
	//void createEntityType(ET, std::string, sf::Color);
	//void createUnitType(std::string, sf::Color, uint, float);
	Entity* createEntity(const EntityType&, Vec2i);
	Unit* createUnit(const UnitType&, Vec2i);
	void updateEntities();
	void selectEntity(Entity*);
	std::list<Entity*> entities;
private:
	uint entityIndex;
	//std::map<ET, EntityType*> entityTypes;
	
};
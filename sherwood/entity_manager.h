#pragma once
#include "types.h"
#include <list>

class EntityType;
class UnitType;
class BuildingType;
class DepositType;
class Map;
class Entity;
class Unit;
class Building;
class Deposit;

class EntityManager {
public:
	EntityManager();
	Entity* createEntity(const EntityType&, const Vec2i);
	Unit* createUnit(const UnitType&, const Vec2i);
	Building* createBuilding(const BuildingType&, const Vec2i);
	Deposit* createResource(const DepositType&, const Vec2i);
	void updateEntities();
	void selectEntity(Entity*);
	std::list<Entity*> entities;
};
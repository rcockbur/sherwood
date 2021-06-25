#pragma once
#include "types.h"
#include <list>
#include <unordered_map>

class UnitType;
class BuildingType;
class DoodadType;
class DepositType;
class Map;
class Unit;
class Doodad;
class Building;
class Deposit;

class EntityManager {
public:
	EntityManager();
	Doodad* createDoodad(const DoodadType&, const Vec2i);
	Deposit* createDeposit(const DepositType&, const Vec2i);
	Unit* createUnit(const UnitType&, const Vec2i);
	Building* createBuilding(const BuildingType&, const Vec2i);
	//void destroyEntity(Entity* entity);
	void updateEntities();
	void selectEntity(Entity*);
	Entity* getEntityAtWorldPos(const Vec2f& worldPosition) const;
	std::unordered_map<int, Entity*> entityMap;
	std::unordered_map<int, Unit*> unitMap;
	std::unordered_map<int, Deposit*> depositMap;
private:
	//std::list<Unit*> units;
};
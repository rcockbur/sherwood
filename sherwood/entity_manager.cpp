#include <assert.h>
#include "entity_manager.h"
#include "map.h"
#include "entity_type.h"
#include "entity.h"
#include "globals.h"

EntityManager::EntityManager() {
	std::cout << "EntityManager created\n";
}

Doodad* EntityManager::createDoodad(const DoodadType& doodadType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Doodad* doodad = new Doodad(doodadType, _tile);
	entities.push_back(doodad);
	return doodad;
}

Deposit* EntityManager::createDeposit(const DepositType& resourceType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Deposit* deposit = new Deposit(resourceType, _tile);
	entities.push_back(deposit);
	return deposit;
}

Unit* EntityManager::createUnit(const UnitType& unitType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Unit* unit = new Unit(unitType, _tile);
	entities.push_back(unit);
	units.push_back(unit);
	return unit;
}

Building* EntityManager::createBuilding(const BuildingType& buildingType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Building* building = new Building(buildingType, _tile);
	entities.push_back(building);
	return building;
}

void EntityManager::updateEntities() {
	for (auto& unit : units) 
		unit->update();
}

void EntityManager::selectEntity(Entity* entity) {
	if (selectedEntity != nullptr)
		selectedEntity->isSelected = false;
	
	selectedEntity = entity;
	selectedEntity->isSelected = true;
	std::cout << "Entity " << entity->id << " is selected" << "\n";
}

Entity* EntityManager::getEntityAtWorldPos(const Vec2f& worldPosition) const {
	for (auto& entity : em.entities) {
		if (entity->bounds.contains(worldPosition)) {
			return entity;
		}
	}
	return nullptr;
}
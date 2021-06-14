#include <assert.h>
#include "entity_manager.h"
#include "map.h"
#include "entity_type.h"
#include "entity.h"
#include "globals.h"

EntityManager::EntityManager() {
	std::cout << "EntityManager created\n";
}


Entity* EntityManager::createEntity(const EntityType& entityType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y) 
		throw std::logic_error("tile is out of bounds");
	
	Entity* entity = new Entity(entityType, _tile);
	entity->color = entity->type.color;
	entities.push_back(entity);
	return entity;
}

Unit* EntityManager::createUnit(const UnitType& unitType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Unit* unit = new Unit(unitType, _tile);
	unit->color = unit->type.color;
	entities.push_back(unit);
	return unit;
}

Building* EntityManager::createBuilding(const BuildingType& buildingType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Building* building = new Building(buildingType, _tile);
	building->color = building->type.color;
	entities.push_back(building);
	return building;
}

Deposit* EntityManager::createResource(const DepositType& resourceType, const Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Deposit* deposit = new Deposit(resourceType, _tile);
	deposit->color = deposit->type.color;
	entities.push_back(deposit);
	return deposit;
}

void EntityManager::updateEntities() {
	for (auto& entity : entities) 
		entity->update();
}

void EntityManager::selectEntity(Entity* entity) {
	if (selectedEntity != nullptr)
		selectedEntity->isSelected = false;
	
	selectedEntity = entity;
	selectedEntity->isSelected = true;
	std::cout << "Entity " << entity->id << " is selected" << "\n";
}
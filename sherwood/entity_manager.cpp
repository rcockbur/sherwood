#include <assert.h>
#include "entity_manager.h"
#include "map.h"
#include "entity_type.h"
#include "entity.h"
#include "globals.h"

EntityManager::EntityManager()
	: entityIndex(0)
{
	std::cout << "EntityManager created\n";
}

void EntityManager::createEntityType(ET id, std::string name, sf::Color color) {
	EntityType* entityType = new EntityType(id, name, color);
	entityTypes.insert(std::pair<ET, EntityType*>(id, entityType));
}

void EntityManager::createUnitType(ET id, std::string name, sf::Color color, uint movePeriod, float moveDistance) {
	UnitType* entityType = new UnitType(id, name, color, movePeriod, moveDistance);
	entityTypes.insert(std::pair<ET, EntityType*>(id, entityType));
}

Entity* EntityManager::createEntity(ET et, Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y) 
		throw std::logic_error("tile is out of bounds");
	
	Entity* entity = new Entity(*entityTypes.at(et), entityIndex++, _tile);
	entity->color = entity->type.color;
	entities.push_back(entity);
	return entity;
}

Unit* EntityManager::createUnit(ET et, Vec2i _tile) {
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y)
		throw std::logic_error("tile is out of bounds");

	Unit* unit = new Unit(static_cast<UnitType&>(*entityTypes.at(et)), entityIndex++, _tile);
	unit->color = unit->type.color;
	entities.push_back(unit);
	return unit;
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
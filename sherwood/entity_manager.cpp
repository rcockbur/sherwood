#include <assert.h>
#include "entity_manager.h"
#include "map.h"
#include "entity_type.h"
#include "entity.h"
#include "globals.h"

EntityManager::EntityManager() {
	std::cout << "EntityManager created\n";
	staticEntityGrid.resize(map.tileCount.x);
	for (int x = 0; x < map.tileCount.x; x++) {
		staticEntityGrid[x].resize(map.tileCount.y);
	}
}

void EntityManager::updateEntities() {
	for (auto& it : unitMap) 
		it.second->update();
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

//gets the entity at the tile
Entity* EntityManager::getEntityFromTile(const Vec2i& tile) const {
	return staticEntityGrid[tile.x][tile.y];
}

Unit* EntityManager::getUnitByID(const int id) const {
	auto it = em.unitMap.find(id);
	return (it == em.unitMap.end()) ? nullptr : it->second;
}

void EntityManager::validateStaticEntityGridAvailable(const Vec2i tile) {
	if (staticEntityGrid[tile.x][tile.y] != nullptr)
		throw std::logic_error("staticEntityGrid slot already occupied");
}
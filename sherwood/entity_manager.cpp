#include <assert.h>
#include "entity_manager.h"
#include "map.h"
#include "entity_style.h"
#include "entity.h"
#include "globals.h"

EntityManager::EntityManager() {
	std::cout << "EntityManager created\n";
}

void EntityManager::updateEntities() {
	for (auto& it : all_units) 
		it.second->update();
}

Entity* EntityManager::getUnitByID(const int id) const {
	auto it = em.all_units.find(id);
	return (it == em.all_units.end()) ? nullptr : it->second;
}

void EntityManager::updateSizes() {
	for (auto it : all_styles) {
		it->updateSize();
	}
}


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
	for (auto& it : units) 
		it.second->update();
}

Unit* EntityManager::getUnitByID(const int id) const {
	auto it = em.units.find(id);
	return (it == em.units.end()) ? nullptr : it->second;
}


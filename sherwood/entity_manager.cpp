#include <SFML/Graphics.hpp>
#include <assert.h>
#include "entity_manager.h"
#include "map.h"
#include <iostream>

extern Map map;

EntityManager::EntityManager()
	: entityIndex(0)
{
	std::cout << "Entity Manager created\n";
}

void EntityManager::createEntityType(ET id, std::string name, sf::Color color, uint movePeriod) 
{
	EntityType* entityType = new EntityType(id, name, color, movePeriod);

	entityTypes.insert(std::pair<ET, EntityType*>(id, entityType));
}

Entity* EntityManager::createEntity(ET et, Vec2i _tile) 
{
	if (_tile.x < 0 || _tile.x >= map.tileCount.x || _tile.y < 0 || _tile.y >= map.tileCount.y) 
		throw std::logic_error("tile is out of bounds");
	
	Entity* entity = new Entity(entityTypes.at(et), entityIndex++, _tile);

	entity->color = entity->type->color;

	entities.push_back(entity);

	return entity;
}

void EntityManager::updateEntities()
{
	for (auto& entity : entities) 
		entity->update();
	
}

std::list<Entity*> EntityManager::getEntities() {
	return entities;
}
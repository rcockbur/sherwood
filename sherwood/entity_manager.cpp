#include <SFML/Graphics.hpp>
#include "entity_manager.h"
#include <iostream>



EntityManager::EntityManager()
{
	std::cout << "Entity Manager created\n";
	createEntityType(ET::DEER, "deer", sf::Color::Blue);
}

EntityType* EntityManager::createEntityType(ET id, std::string name, sf::Color color) 
{
	entityTypes.insert(std::pair<ET, EntityType>(id, EntityType(id, name, color)));

	return &entityTypes.at(id);
}

Entity* EntityManager::createEntity(ET et, Vec2i _tile) 
{
	Entity entity(&entityTypes.at(et), entityIndex++, _tile);

	entity.color = entity.type->color;

	entities.push_back(entity);

	return &entities.back();
}

void EntityManager::updateEntities()
{
	for (auto& entity : entities) {
		entity.update();
	}
}
#include <SFML/Graphics.hpp>
#include "entity_manager.h"
#include "typedefs.h"

Entity* EntityManager::createEntity(Position _pos) {
	Entity* entity = new Entity(id_index++);
	entities.push_back(entity);

	Position* position = new Position(_pos);
	entity->position = position;

	Actor* actor = new Actor(sf::Color::Blue);
	entity->actor = actor;

	return entity;
}
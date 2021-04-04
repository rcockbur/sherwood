#include <SFML/Graphics.hpp>
#include "graphics.h"
#include <assert.h>
#include "entity_manager.h"
#include "map.h"
#include <iostream>

extern Colors colors;
extern Map map;

EntityManager em = EntityManager();

void initEntities()
{
	em.createEntityType(ET::DEER, "deer", colors.yellow, 10);

	Entity* entity = em.createEntity(ET::DEER, Vec2i(0, 0));

	em.createEntity(ET::DEER, Vec2i(2, 0));
	em.createEntity(ET::DEER, Vec2i(3, 0));

	std::list<Vec2i> path{ Vec2i(0,1), Vec2i(0,2), Vec2i(0,3), Vec2i(0,4), Vec2i(0,5) };
	Move* move = new Move(*entity, path);
	entity->addAbility(move);

	std::list<Vec2i> path2{ Vec2i(1,5), Vec2i(2,5), Vec2i(3,5), Vec2i(4,5), Vec2i(5,5) };
	Move* move2 = new Move(*entity, path2);
	entity->addAbility(move2);
}

EntityManager::EntityManager()
	: entityIndex(0)
{
	std::cout << "EntityManager created\n";
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

std::list<Entity*> EntityManager::getEntities() 
{
	return entities;
}
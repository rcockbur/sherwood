#include "globals.h"
#include "map.h"
#include "entity_manager.h"
#include "ability.h"
#include <list>
#include <iostream>



EntityManager em = EntityManager();
uint tic(0);
uint targetFPS(10);
float actualFPS(targetFPS);

Colors colors;

void initGlobals() {
	

	em.createEntityType(ET::DEER, "deer", colors.blue, 30);
	 
	Entity* entity = em.createEntity(ET::DEER, Vec2i(0, 0));

	em.createEntity(ET::DEER, Vec2i(2, 0));
	em.createEntity(ET::DEER, Vec2i(9, 0));

	std::list<Vec2i> path{ Vec2i(0,1), Vec2i(0,2), Vec2i(0,3), Vec2i(0,4), Vec2i(0,5) };
	Move* move = new Move(*entity, path);
	entity->addAbility(move);

}
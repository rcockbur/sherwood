#include "globals.h"
#include "map.h"
#include "entity_manager.h"
#include "ability.h"
#include <list>
#include <iostream>

sf::RenderWindow window(sf::VideoMode(400, 400), "Sherwood");
sf::Color Grey(100, 100, 100);
Map map({ 10,10 }, { 15., 15. }, 1., Grey);
EntityManager em = EntityManager();
Vec2f cameraPos{ -21, -21 };
uint tic(0);
uint targetFPS(60);

void initGlobals() {
	window.setFramerateLimit(targetFPS);

	em.createEntityType(ET::DEER, "deer", sf::Color::Blue, 60);
	 
	Entity* entity = em.createEntity(ET::DEER, Vec2i(0, 0));

	em.createEntity(ET::DEER, Vec2i(2, 0));
	em.createEntity(ET::DEER, Vec2i(9, 0));

	std::list<Vec2i> path{ Vec2i(0,1), Vec2i(0,2), Vec2i(0,3), Vec2i(0,4), Vec2i(0,5) };
	Move* move = new Move(*entity, path);
	entity->addAbility(move);

}
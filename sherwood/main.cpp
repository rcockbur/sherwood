#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"

int main()
{
	initWindow();
	initEntityTypes();
	em.createUnit(person, Vec2i(2, 1));
	em.createUnit(person, Vec2i(3, 1));
	Unit* peter = em.createUnit(person, Vec2i(2, 2));

	em.createDoodad(rock, Vec2i(5, 5));
	

	em.createDeposit(berryBush, Vec2i(3, 4));
	em.createDeposit(berryBush, Vec2i(20, 20));
	em.createDeposit(tree, Vec2i(5, 2));

	Building* petersHome = em.createBuilding(house, Vec2i(3, 8));

	peter->setHome(petersHome);

	while (renderWindow.isOpen()) {
		input.handleInput();
		em.updateEntities();
		graphics.draw();
		if (hasPrinted) std::cout << "---------------------" << std::endl;
		hasPrinted = false;
		++tic;
		dt = deltaClock.restart();
		actualFPS = 1 / dt.asSeconds();
	}
    return 0;
}
#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"

int main()
{
	initWindow();
	initEntityTypes();

	new Doodad(rock, Vec2i(4, 0));

	Building* myHome = new Building(house, Vec2i(0, 3));

	(new Unit(person, Vec2i(0, 0)))->setHome(*myHome);
	(new Unit(person, Vec2i(1, 0)))->setHome(*myHome);
	(new Unit(person, Vec2i(2, 0)))->setHome(*myHome);

	new Deposit(berryBush, Vec2i(5, 3));
	new Deposit(berryBush, Vec2i(4, 12));
	new Deposit(berryBush, Vec2i(20, 20));

	new Deposit(tree, Vec2i(8, 0));
	new Deposit(tree, Vec2i(9, 0));
	new Deposit(tree, Vec2i(9, 1));

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
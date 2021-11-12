#include "globals.h"
#include "entity.h"
#include "input.h"
#include "entity_manager.h"

int main()
{
	initWindow();
	initEntityStyles();

	new Doodad(ROCK, Vec2i(4, 0));

	Building* myHome = new Building(HOUSE, Vec2i(7, 9));

	new Building(MILL, Vec2i(8, 9));

	(new Unit(PERSON, Vec2i(0, 0)))->setHome(*myHome);
	(new Unit(PERSON, Vec2i(1, 0)))->setHome(*myHome);
	(new Unit(PERSON, Vec2i(2, 0)));

	new Deposit(BERRY_BUSH, Vec2i(5, 3));
	new Deposit(BERRY_BUSH, Vec2i(4, 12));
	new Deposit(BERRY_BUSH, Vec2i(20, 21));

	new Deposit(FISH, { 5, 8 });
	new Deposit(FISH, Vec2i(15, 4));
	new Deposit(FISH, Vec2i(13, 7));
	new Deposit(FISH, Vec2i(10, 11));
	new Deposit(FISH, Vec2i(1, 17));
	new Deposit(FISH, Vec2i(6, 28));
	new Deposit(FISH, Vec2i(15, 28));
	new Deposit(FISH, Vec2i(26, 24));
	new Deposit(FISH, Vec2i(34, 21));
	new Deposit(FISH, Vec2i(35, 16));
	new Deposit(FISH, Vec2i(34, 5));
	new Deposit(FISH, Vec2i(30, 5));
	new Deposit(FISH, Vec2i(21, 9));
	new Deposit(FISH, Vec2i(34, 1));
	new Deposit(FISH, Vec2i(24, 0));
	new Deposit(FISH, Vec2i(11, 1));
	new Deposit(FISH, Vec2i(1, 7));

	new Deposit(TREE, Vec2i(8, 0));
	new Deposit(TREE, Vec2i(9, 0));
	new Deposit(TREE, Vec2i(9, 1));

	new Deposit(GOLD_MINE, Vec2i(30, 20));

	new Deposit(STONE_MINE, Vec2i(24, 24));

	float lastFPSUpdate = gameClock.getElapsedTime().asSeconds();
	while (renderWindow.isOpen()) {
		handleInput();
		em.updateEntities();
		graphics.draw();
		if (hasPrinted) std::cout << "---------------------" << std::endl;
		hasPrinted = false;
		++tics;
		seconds = tics / TICS_PER_MINUTE;
		dt = deltaClock.restart();
		
		if ((gameClock.getElapsedTime().asSeconds() - lastFPSUpdate) >= 0.3f) {
			lastFPSUpdate = gameClock.getElapsedTime().asSeconds();
			actualFPS = 1 / dt.asSeconds();
		}
		
	}
    return 0;
}
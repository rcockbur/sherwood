#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"

int main()
{
	initWindow();
	em.createUnit(person, Vec2i(2, 1));
	em.createUnit(person, Vec2i(3, 1));
	em.createUnit(person, Vec2i(2, 2));

	em.createEntity(rock, Vec2i(5, 5));

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
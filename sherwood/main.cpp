#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"

int main()
{
	em.createUnitType(ET::DEER, "deer", color.brown, 1, 3.0f);

	em.createUnit(ET::DEER, Vec2i(2, 1));
	em.createUnit(ET::DEER, Vec2i(3, 1));
	em.createUnit(ET::DEER, Vec2i(2, 2));

	while (wm.window.isOpen()) {
		im.handleInput();
		em.updateEntities();
		gm.draw();
		if (hasPrinted) std::cout << "---------------------" << std::endl;
		hasPrinted = false;
		++tic;
		dt = deltaClock.restart();
		wm.actualFPS = 1 / dt.asSeconds();
	}
    return 0;
}
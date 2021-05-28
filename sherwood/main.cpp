#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "colors.h"

int main()
{
	em.createEntityType(ET::DEER, "deer", colors.brown, 1, 5.0f);

	em.createEntity(ET::DEER, Vec2i(0, 0));
	em.createEntity(ET::DEER, Vec2i(0, 1));
	em.createEntity(ET::DEER, Vec2i(1, 11));
	em.createEntity(ET::DEER, Vec2i(2, 1));
	em.createEntity(ET::DEER, Vec2i(3, 1));
	em.createEntity(ET::DEER, Vec2i(2, 2));

	Entity* entity = em.createEntity(ET::DEER, Vec2i(0, 2));

	std::list<Vec2i> path{ Vec2i(0,3), Vec2i(0,4), Vec2i(0,5) };
	Move* move = new Move(*entity, path);
	entity->addAbility(move);

	std::list<Vec2i> path2{ Vec2i(1,5), Vec2i(2,5), Vec2i(3,5), Vec2i(4,5), Vec2i(5,5) };
	Move* move2 = new Move(*entity, path2);
	entity->addAbility(move2);

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
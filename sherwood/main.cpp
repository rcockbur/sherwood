#include "entity_manager.h"
#include "graphics_manager.h"
#include "colors.h"
#include "ability.h"
#include "map.h"
#include "entity.h"
#include <list>
#include "window_manager.h"

extern Colors colors;

uint tic(0);

bool showGrid = true;

int main()
{
	WindowManager wm("Sherwood", 30);
	Map map("data/map.txt");
	GraphicsManager gm(map, wm);
	EntityManager em(map);
	
	em.createEntityType(ET::DEER, "deer", colors.yellow, 60);

	em.createEntity(ET::DEER, Vec2i(0, 0));
	em.createEntity(ET::DEER, Vec2i(0, 1));
	em.createEntity(ET::DEER, Vec2i(1, 0));
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

	bool hasPrinted = false;

	sf::Clock deltaClock;
	sf::Time dt = deltaClock.restart();
	std::cout << "Mainloop started\n";
	while (wm.window.isOpen()) {
		sf::Event event;
		while (wm.window.pollEvent(event)) {
			Vec2f screen_pos((float)sf::Mouse::getPosition(wm.window).x, (float)sf::Mouse::getPosition(wm.window).y);
			
			switch (event.type) {
			case sf::Event::Closed:
				wm.window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case(sf::Keyboard::Escape):
					wm.window.close();
					break;
				case(sf::Keyboard::Q):
					wm.window.close();
					break;
				case(sf::Keyboard::W):
					break;
				case(sf::Keyboard::A):
					break;
				case(sf::Keyboard::S):
					break;
				case(sf::Keyboard::D):
					break;
				case(sf::Keyboard::G):
					showGrid = !showGrid;
					break;
				case(sf::Keyboard::Up):
					wm.mapView.move(Vec2f(0, -5));
					break;
				case(sf::Keyboard::Down):
					wm.mapView.move(Vec2f(0, 5));
					break;
				case(sf::Keyboard::Left):
					wm.mapView.move(Vec2f(-5, 0));
					break;
				case(sf::Keyboard::Right):
					wm.mapView.move(Vec2f(5, 0));
					break;
				case(sf::Keyboard::Add):
					wm.updateFPS(wm.targetFPS + 1);
					break;
				case(sf::Keyboard::Subtract):
					wm.updateFPS(wm.targetFPS - 1);
					break;
				default:
					break;
				}
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button) {
				case(sf::Mouse::Left):
					wm.handleScreenClick(screen_pos);
					break;
				default:
					break;
				}
			default:
				break;
			} 
		}

		em.updateEntities();
		gm.draw();
		
		if (hasPrinted)
			std::cout << "---------------------------------------------------------" << std::endl;
		hasPrinted = false;
		++tic;
		dt = deltaClock.restart();
		wm.actualFPS = 1 / dt.asSeconds();
	}

    return 0;
}
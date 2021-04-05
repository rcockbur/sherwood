#include <list>
#include "entity_manager.h"
#include "graphics_manager.h"
#include "colors.h"
#include "ability.h"
#include "map.h"
#include "entity.h"

extern sf::RenderWindow window;
extern sf::View mapView;
extern Colors colors;

uint tic(0);
uint targetFPS;
float actualFPS;

void updateFPS(uint fps) {
	targetFPS = fps;
	window.setFramerateLimit(targetFPS);
}

int main()
{
	Map map("data/map.txt");
	EntityManager em(map);
	GraphicsManager gm(map, colors.grey);
	
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

	bool hasPrinted = false;

	sf::Clock deltaClock;
	sf::Time dt = deltaClock.restart();
	updateFPS(30);
	std::cout << "Mainloop started\n";
	while (window.isOpen()) {
		sf::Clock clock;
		sf::Event event;
		while (window.pollEvent(event)) {
			//sf::Vector2f screen_pos((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
			//sf::Vector2f world_pos = screen_pos_to_world_pos(screen_pos);
			//sf::Vector2i tile = world_pos_to_tile(world_pos);
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case(sf::Keyboard::Escape):
					window.close();
					break;
				case(sf::Keyboard::Q):
					window.close();
					break;
				case(sf::Keyboard::W):
					break;
				case(sf::Keyboard::A):
					break;
				case(sf::Keyboard::S):
					break;
				case(sf::Keyboard::D):
					break;
				case(sf::Keyboard::Up):
					mapView.move(Vec2f(0, -5));
					break;
				case(sf::Keyboard::Down):
					mapView.move(Vec2f(0, 5));
					break;
				case(sf::Keyboard::Left):
					mapView.move(Vec2f(-5, 0));
					break;
				case(sf::Keyboard::Right):
					mapView.move(Vec2f(5, 0));
					break;
				case(sf::Keyboard::Add):
					updateFPS(targetFPS + 1);
					break;
				case(sf::Keyboard::Subtract):
					updateFPS(targetFPS - 1);
					break;
				default:
					break;
				} //switch (event.key.code)
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button) {
				case(sf::Mouse::Left):
					//has_printed = true;
					//std::cout << "screen_pos:" << screen_pos.x << ", " << screen_pos.y << std::endl;
					//std::cout << "world_pos: " << world_pos.x << ", " << world_pos.y << std::endl;
					//std::cout << "tile:   " << tile.x << ", " << tile.y << std::endl;
					//select_entity(world_pos);
					break;
				default:
					break;
				} //switch (event.mouseButton.button)
			default:
				break;
			} //switch (event.type)
		}

		
		em.updateEntities();
		gm.draw();
		
		if (hasPrinted)
			std::cout << "---------------------------------------------------------" << std::endl;
		hasPrinted = false;
		++tic;
		dt = deltaClock.restart();
		actualFPS = 1 / dt.asSeconds();
	}

    return 0;
}
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity_manager.h"
#include "graphics.h"

extern sf::RenderWindow window;
extern Vec2f cameraPos;
extern EntityManager em;
extern uint tic;
extern uint targetFPS;

int main()
{
	initGlobals();
	initGraphics();

	bool hasPrinted = false;
	
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
					cameraPos.y = cameraPos.y - 5;
					break;
				case(sf::Keyboard::Down):
					cameraPos.y = cameraPos.y + 5;
					break;
				case(sf::Keyboard::Left):
					cameraPos.x = cameraPos.x - 5;
					break;
				case(sf::Keyboard::Right):
					cameraPos.x = cameraPos.x + 5;
					break;
				case(sf::Keyboard::Add):
					targetFPS++;
					break;
				case(sf::Keyboard::Subtract):
					targetFPS--;
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

		window.clear();
		em.updateEntities();
		drawMap();
		drawEntities();
		drawText();
		window.display();
		if (hasPrinted)
			std::cout << "---------------------------------------------------------" << std::endl;
		hasPrinted = false;
		++tic;
	}

    return 0;
}
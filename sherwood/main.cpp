#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	bool has_printed = false;
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
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					break;
				}
				if (event.key.code == sf::Keyboard::Q) {
					window.close();
					break;
				}
				if (event.key.code == sf::Keyboard::W) {
					//move_selected_by(sf::Vector2f(0, -1));
					break;
				}
				if (event.key.code == sf::Keyboard::A) {
					//move_selected_by(sf::Vector2f(-1, 0));
					break;
				}
				if (event.key.code == sf::Keyboard::S) {
					//move_selected_by(sf::Vector2f(0, 1));
					break;
				}
				if (event.key.code == sf::Keyboard::D) {
					//move_selected_by(sf::Vector2f(1, 0));
					break;
				}
				if (event.key.code == sf::Keyboard::Up) {
					//camera_pos.y = camera_pos.y - 5;
					break;
				}
				if (event.key.code == sf::Keyboard::Down) {
					//camera_pos.y = camera_pos.y + 5;
					break;
				}
				if (event.key.code == sf::Keyboard::Left) {
					//camera_pos.x = camera_pos.x - 5;
					break;
				}
				if (event.key.code == sf::Keyboard::Right) {
					//camera_pos.x = camera_pos.x + 5;
					break;
				}
				if (event.key.code == sf::Keyboard::B) {
					//try_spawn_block(tile);
					break;
				}
				if (event.key.code == sf::Keyboard::U) {
					//try_spawn_unit(tile);
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					//has_printed = true;
					//std::cout << "screen_pos:" << screen_pos.x << ", " << screen_pos.y << std::endl;
					//std::cout << "world_pos: " << world_pos.x << ", " << world_pos.y << std::endl;
					//std::cout << "tile:   " << tile.x << ", " << tile.y << std::endl;
					//select_entity(world_pos);
				}
			default:
				break;
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
		if (has_printed)
			std::cout << "---------------------------------------------------------" << std::endl;
		has_printed = false;
	}

    return 0;
}
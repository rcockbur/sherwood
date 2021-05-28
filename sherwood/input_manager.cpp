#include "input_manager.h"
#include "window_manager.h"
#include "map.h"
#include "entity.h"
#include "entity_manager.h"
#include "globals.h"
#include "ability.h"
#include "entity.h"

InputManager::InputManager()
{

}

void InputManager::handleInput()
{
	sf::Event event;
	while (wm.window.pollEvent(event)) {
		Vec2f screen_pos((float)sf::Mouse::getPosition(wm.window).x, (float)sf::Mouse::getPosition(wm.window).y);

		switch (event.type) {
		case sf::Event::Closed:
			wm.window.close();
			break;
		case sf::Event::KeyPressed:
			handleKeyPress(event.key.code);
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button) {
			case(sf::Mouse::Left):
				handleScreenClick(screen_pos, false);
				break;
			case(sf::Mouse::Right):
				handleScreenClick(screen_pos, true);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void InputManager::handleScreenClick(const Vec2f& screenPos, bool isRightClick) {
	std::cout << "ScreenPosition:" << screenPos.x << "," << screenPos.y << "\n";

	if (wm.viewportRect.contains(screenPos)) {
		Vec2f worldPos = wm.screenToWorld(screenPos);
		handleWorldClick(worldPos, isRightClick);
	}
	else {
		std::cout << "Out of bounds\n";
	}
}

void InputManager::handleWorldClick(const Vec2f& worldPosition, bool isRightClick) {
	std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
	Vec2i clickedTile = wm.worldToTile(worldPosition);
	std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
	if (isRightClick) {
		if (selectedEntity != nullptr && selectedEntity->tile != clickedTile) {
			//std::list<Vec2i> path{ clickedTile };
			//Move* move = new Move(*selectedEntity, path);
			//selectedEntity->setAbility(move);
			astar.clear();
			if (astar.search(selectedEntity->tile, clickedTile)) {
				std::list<Vec2i> path;
				int c = astar.path(path);
				Move* move = new Move(*selectedEntity, path);
				selectedEntity->setAbility(move);
			}
		}
	}
	else {
		for (auto& entity : em.entities) {
			if (entity->bounds.contains(worldPosition)) {
				em.selectEntity(entity);
			}
		}
	}
	
}

void InputManager::updateFPS(uint fps) {
	wm.targetFPS = fps;
	wm.window.setFramerateLimit(wm.targetFPS);
}

void InputManager::handleKeyPress(sf::Keyboard::Key code) {
	switch (code) {
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
		updateFPS(wm.targetFPS + 1);
		break;
	case(sf::Keyboard::Subtract):
		updateFPS(wm.targetFPS - 1);
		break;
	default:
		break;
	}
}
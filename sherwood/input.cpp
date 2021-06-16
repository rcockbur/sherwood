#include "input.h"
#include "map.h"
#include "entity.h"
#include "entity_manager.h"
#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "utility.h"

Input::Input()
{

}

void Input::handleInput()
{
	sf::Event event;
	while (renderWindow.pollEvent(event)) {
		Vec2f screen_pos((float)sf::Mouse::getPosition(renderWindow).x, (float)sf::Mouse::getPosition(renderWindow).y);

		switch (event.type) {
		case sf::Event::Closed:
			renderWindow.close();
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

void Input::handleScreenClick(const Vec2f& screenPos, bool isRightClick) {
	std::cout << "ScreenPosition:" << screenPos.x << "," << screenPos.y;

	if (VIEWPORT_RECT.contains(screenPos)) {
		Vec2f worldPos = screenToWorld(screenPos);
		handleWorldClick(worldPos, isRightClick);
	}
	else {
		std::cout << "Out of bounds\n";
	}
	std::cout << "\n";
}

void Input::handleWorldClick(const Vec2f& worldPosition, bool isRightClick) {
	std::cout << "  WorldPosition:" << worldPosition.x << "," << worldPosition.y;
	Vec2i clickedTile = worldToTile(worldPosition);
	std::cout << "  Tile:" << clickedTile.x << "," << clickedTile.y;
	Unit* selectedUnit = dynamic_cast<Unit*>(selectedEntity);
	if (isRightClick) {
		if (selectedUnit) {
			if (selectedEntity != nullptr && worldToTile(selectedEntity->position) != clickedTile) {
				astar.clear();
				if (showPathfinding) renderWindow.setFramerateLimit(1000);					
				if (astar.search(worldToTile(selectedUnit->position), clickedTile)) {
					std::list<Vec2i> path = astar.path();
					Move* move = new Move(*selectedUnit, path);
					selectedUnit->setAbility(move);
				}
				if (showPathfinding) renderWindow.setFramerateLimit(targetFPS);
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

void Input::updateFPS(int fps) {
	targetFPS = fps;
	renderWindow.setFramerateLimit(targetFPS);
}

void Input::handleKeyPress(sf::Keyboard::Key code) {
	switch (code) {
	case(sf::Keyboard::Escape):
		renderWindow.close();
		break;
	case(sf::Keyboard::Q):
		renderWindow.close();
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
	case(sf::Keyboard::P):
		showPathfinding = !showPathfinding;
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
	}
}
#include "input.h"
#include "map.h"
#include "entity.h"
#include "entity_manager.h"
#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "utility.h"
#include "actions.h"

void handleInput()
{
	handleKeysDown();
	sf::Event event;
	while (renderWindow.pollEvent(event)) {
		mouseScreenPos = Vec2f((float)sf::Mouse::getPosition(renderWindow).x, (float)sf::Mouse::getPosition(renderWindow).y);
		if (ui.viewportPanel.containsScreenPos(mouseScreenPos)) {
			mouseWorldPos = screenToWorld(mouseScreenPos);
			mouseTile = worldToTile(mouseWorldPos);
			if (map.containsWorldPos(mouseWorldPos) == false) {
				mouseWorldPos = Vec2f(-1, -1);
				mouseTile = Vec2i(-1, -1);
			}
		}
		else {
			mouseWorldPos = Vec2f(-1, -1);
			mouseTile = Vec2i(-1, -1);
		}
		switch (event.type) {
		case sf::Event::Closed:
			renderWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleKeyPress(event.key.code);
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button) {
			case(sf::Mouse::Left):
				ui.hud.handleClick(true);
				break;
			case(sf::Mouse::Right):
				ui.hud.handleClick(false);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void handleKeysDown() {
	shiftIsDown = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	Vec2f cameraMove(-CAMERA_SPEED, -CAMERA_SPEED);
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) cameraMove.x += CAMERA_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) cameraMove.x += CAMERA_SPEED;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) cameraMove.y += CAMERA_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) cameraMove.y += CAMERA_SPEED;
	mapView.move(cameraMove);
}

void handleKeyPress(sf::Keyboard::Key code) {
	switch (code) {
	case(sf::Keyboard::Q):
		renderWindow.close();
		break;
	case(sf::Keyboard::Delete):
		if (selectedEntity != nullptr)
			delete selectedEntity;
		break;
	case(sf::Keyboard::Escape):
		if (placementBuildingType) {
			placementBuildingType = nullptr;
		}
		else if (selectedEntity)
			em.deselectEntity(selectedEntity);
		break;
	case(sf::Keyboard::G):
		showGrid = !showGrid;
		break;
	case(sf::Keyboard::P):
		showPathfinding = !showPathfinding;
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

void updateFPS(int fps) {
	targetFPS = fps;
	renderWindow.setFramerateLimit(targetFPS);
}


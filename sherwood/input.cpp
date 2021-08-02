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
	handleMousePosition();
	sf::Event event;
	while (renderWindow.pollEvent(event)) {
		
		switch (event.type) {
		case sf::Event::Closed:
			renderWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleKeyPress(event.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button) {
			case(sf::Mouse::Left):
				if (ui.viewportPanel.containsScreenPos(mouseScreenPos)) {
					handleWorldClick(true, true);
				}
				else {
					ui.hud.handleClick(true, true);
				}
				break;
			case(sf::Mouse::Right):
				if (ui.viewportPanel.containsScreenPos(mouseScreenPos)) {
					handleWorldClick(false, true);
				}
				else {
					ui.hud.handleClick(false, true);
				}
				break;
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button) {
			case(sf::Mouse::Left):
				if (ui.viewportPanel.containsScreenPos(mouseScreenPos) || selectionRectActive) {
					handleWorldClick(true, false);
				}
				else {
					ui.hud.handleClick(true, false);
				}
				break;
			case(sf::Mouse::Right):
				if (ui.viewportPanel.containsScreenPos(mouseScreenPos)) {
					handleWorldClick(false, false);
				}
				else {
					ui.hud.handleClick(false, false);
				}
				break;
			default:
				break;
			}
			break;
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

void handleMousePosition() {
	mouseScreenPos = Vec2f((float)sf::Mouse::getPosition(renderWindow).x, (float)sf::Mouse::getPosition(renderWindow).y);
	mouseWorldPos = screenToWorld(mouseScreenPos);
	mouseTile = worldToTile(mouseWorldPos);
}

void handleKeyPress(sf::Keyboard::Key code) {
	switch (code) {
	case(sf::Keyboard::Q):
		renderWindow.close();
		break;
	case(sf::Keyboard::Delete):
		for (auto it = selectedEntities.begin(); it != selectedEntities.end(); ) {
			delete* it++;
		}
		break;
	case(sf::Keyboard::Escape):
		if (placementBuildingStyle) {
			placementBuildingStyle = nullptr;
		}
		else {
			for (auto it = selectedEntities.begin(); it != selectedEntities.end(); ) {
				(*it++)->deselect();
			}
		}
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
	if (fps > 0) {
		targetFPS = fps;
		renderWindow.setFramerateLimit(targetFPS);
	}
}


#include "input.h"
#include "map.h"
#include "entity.h"
#include "entity_manager.h"
#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "utility.h"
#include "actions.h"
#include "entity_style.h"
#include "SFML/Window/Event.hpp"

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
				ui.hud.handleClick(true, true);
				break;
			case(sf::Mouse::Right):
				ui.hud.handleClick(false, true);
				break;
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button) {
			case(sf::Mouse::Left):
				ui.hud.handleClick(true, false);
				break;
			case(sf::Mouse::Right):
				ui.hud.handleClick(false, false);
				break;
			default:
				break;
			}
			break;
		case sf::Event::MouseWheelMoved:
			int wheelMove = event.mouseWheel.delta;
			zoomCamera(wheelMove);
			break;
		}
	}
}

void handleKeysDown() {
	shiftIsDown = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	Vec2f cameraMove(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) cameraMove.x -= CAMERA_SPEED / zoom;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) cameraMove.x += CAMERA_SPEED / zoom;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) cameraMove.y -= CAMERA_SPEED / zoom;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) cameraMove.y += CAMERA_SPEED / zoom;
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
		deleteEntities(selectedEntities);
		break;
	case(sf::Keyboard::Escape):
		if (placementEntityStyle) {
			placementEntityStyle = nullptr;
		}
		else {
			deselectAll();
		}
		break;
	case(sf::Keyboard::G):
		showGrid = !showGrid;
		break;
	case(sf::Keyboard::P):
		showPaths = !showPaths;
		break;
	case(sf::Keyboard::F):
		showPathfinding = !showPathfinding;
		break;
	case(sf::Keyboard::Add):
		updateFPS(targetFPS + 1);
		break;
	case(sf::Keyboard::S):
		map.saveMapData();
		break;
	case(sf::Keyboard::Subtract):
		updateFPS(targetFPS - 1);
		break;
	case(sf::Keyboard::L):
		if (map.isWithinBounds(mouseTile)) {
			map.setTerrainAtTile(mouseTile, 1);
		}
		break;
	case(sf::Keyboard::W):
		if (map.isWithinBounds(mouseTile)) {
			map.setTerrainAtTile(mouseTile, 0);
		}
		break;
	default:
		break;
	}
}

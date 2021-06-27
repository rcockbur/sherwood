#include "input.h"
#include "map.h"
#include "entity.h"
#include "entity_manager.h"
#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "utility.h"
#include "actions.h"

Input::Input() :
	VIEWPORT_RECT(VIEWPORT_OFFSET[0], VIEWPORT_OFFSET[1], VIEWPORT_SIZE[0], VIEWPORT_SIZE[1])
{}

void Input::handleInput()
{
	handleKeysDown();
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

void Input::handleKeysDown() {
	shiftIsDown = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	Vec2f cameraMove(-CAMERA_SPEED, -CAMERA_SPEED);
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) cameraMove.x += CAMERA_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) cameraMove.x += CAMERA_SPEED;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) cameraMove.y += CAMERA_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) cameraMove.y += CAMERA_SPEED;
	mapView.move(cameraMove);
}

void Input::handleScreenClick(const Vec2f& screenPos, bool isRightClick) {
	//std::cout << "ScreenPosition:" << screenPos.x << "," << screenPos.y << "\n";
	if (VIEWPORT_RECT.contains(screenPos)) {
		Vec2f worldPos = screenToWorld(screenPos);
		handleWorldClick(worldPos, isRightClick);
	}
	else {
		//std::cout << "Out of bounds\n";
	}
}

void Input::handleWorldClick(const Vec2f& worldPosition, bool isRightClick) {
	//std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
	Vec2i clickedTile = worldToTile(worldPosition);
	//std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
	Entity* clickedEntity = em.getEntityAtWorldPos(worldPosition);
	if (isRightClick) {
		Unit* selectedUnit = dynamic_cast<Unit*>(selectedEntity);
		if (selectedUnit != nullptr) {
			Deposit* clickedDeposit = dynamic_cast<Deposit*>(clickedEntity);
			Building* clickedBuilding = dynamic_cast<Building*> (clickedEntity);
			if (clickedDeposit != nullptr) {
				unitHarvestDeposit(*selectedUnit, *clickedDeposit);
			}
			else if (clickedBuilding != nullptr) {
				if (*clickedBuilding == selectedUnit->homeLookup && selectedUnit->carryAmmount > 0) {
					unitReturnResources(*selectedUnit);
				}
			}
			else if (selectedEntity->tile != clickedTile) {
				unitMoveToTile(*selectedUnit, clickedTile);
			}
		}
	}
	else {
		if (clickedEntity != nullptr) {
			em.selectEntity(clickedEntity);
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
	//case(sf::Keyboard::Up):
	//	mapView.move(Vec2f(0, -CAMERA_SPEED));
	//	break;
	//case(sf::Keyboard::Down):
	//	mapView.move(Vec2f(0, CAMERA_SPEED));
	//	break;
	//case(sf::Keyboard::Left):
	//	mapView.move(Vec2f(-CAMERA_SPEED, 0));
	//	break;
	//case(sf::Keyboard::Right):
	//	mapView.move(Vec2f(CAMERA_SPEED, 0));
	//	break;
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
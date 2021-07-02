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
	VIEWPORT_RECT(ui.viewportPanel.getInnerPosition(), ui.viewportPanel.getSize())
{
	ui.viewportPanel.setCallback(handleWorldClick);
}

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
				handleScreenClick(screen_pos, true);
				break;
			case(sf::Mouse::Right):
				handleScreenClick(screen_pos, false);
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

void Input::handleScreenClick(const Vec2f& screenPos, bool isLeftClick) {
	ui.hud.handleClick(screenPos, isLeftClick);
}

void handleWorldClick(const Vec2f screenPos, const bool isLeftClick) {
	//std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
	Vec2f worldPosition = screenToWorld(screenPos);
	Vec2i clickedTile = worldToTile(worldPosition);
	//std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
	Entity* clickedEntity = em.getEntityAtWorldPos(worldPosition);
	if (isLeftClick) {
		if (clickedEntity != nullptr) {
			em.selectEntity(clickedEntity);
		}
	}
	else {
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
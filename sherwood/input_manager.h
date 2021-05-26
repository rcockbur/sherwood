#pragma once
#include "types.h"

class Map;
class WindowManager;
class EntityManager;

class InputManager {
public:
	InputManager();
	void handleInput();
	void handleScreenClick(const Vec2f& screenPosition, bool isRightClick);
	void handleWorldClick(const Vec2f& worldPosition, bool isRightClick);
	void updateFPS(uint fps);
	void handleKeyPress(sf::Keyboard::Key);
};

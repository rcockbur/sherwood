#pragma once
#include "types.h"

class Map;
class Window;
class EntityManager;

class Input {
	const sf::Rect<float> VIEWPORT_RECT;
public:
	Input();
	void handleInput();
	void handleScreenClick(const Vec2f& screenPosition, bool isRightClick);
	void handleWorldClick(const Vec2f& worldPosition, bool isRightClick);
	void updateFPS(int fps);
	void handleKeyPress(sf::Keyboard::Key);
};

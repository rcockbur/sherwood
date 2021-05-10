#pragma once
#include "globals.h"

class Map;
class WindowManager;
class EntityManager;

class InputManager {
public:
	InputManager(Map& map, EntityManager& em, WindowManager& wm);
	void handleScreenClick(const Vec2f screenPosition);
	void handleWorldClick(const Vec2f worldPosition);
	void updateFPS(uint fps);
private:
	Map& map;
	WindowManager& wm;
	EntityManager& em;
};

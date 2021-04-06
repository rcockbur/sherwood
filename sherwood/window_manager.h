#pragma once
#include "globals.h"

class GraphicsManager;



class WindowManager {
public:
	uint targetFPS;
	float actualFPS;
	sf::View mapView;
	sf::RenderWindow window;
	WindowManager(std::string windowName, uint targetFPS);
	Vec2i worldToTile(const Vec2f);
	Vec2f tileToWorld(const Vec2i);
	void handleScreenClick(const Vec2f screenPosition);
	void handleWorldClick(const Vec2f worldPosition);
	void updateFPS(uint fps);
};

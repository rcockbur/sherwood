#pragma once
#include "types.h"

class GraphicsManager;
class Map;


class WindowManager {
public:
	uint targetFPS;
	float actualFPS;
	sf::View mapView;
	sf::RenderWindow window;
	const Vec2f gridSize;

	WindowManager(std::string windowName, uint targetFPS);
	Vec2i worldToTile(const Vec2f);
	Vec2f tileToWorld(const Vec2i);
	Vec2f screenToWorld(const Vec2f);
private:
	const Vec2f calculateGridSize(const Vec2i& tileCount);

};

#pragma once
#include "globals.h"

class GraphicsManager;
class Map;


class WindowManager {
public:
	Map& map;
	uint targetFPS;
	float actualFPS;
	sf::View mapView;
	sf::RenderWindow window;
	const Vec2f gridSize;

	WindowManager(Map& map, std::string windowName, uint targetFPS);
	Vec2i worldToTile(const Vec2f);
	Vec2f tileToWorld(const Vec2i);
	Vec2f screenToWorld(const Vec2f);
private:
	const Vec2f calculateGridSize(const Vec2i& tileCount);

};

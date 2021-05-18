#pragma once
#include "types.h"

class GraphicsManager;
class Map;


class WindowManager {
public:
	

	const float lineWidthHalf;
	const float lineWidth;
	const Vec2f tileSize;
	const Vec2f entitySize;
	const Vec2u windowSize;
	const float windowPaddingTop;
	const float windowPaddingLeft;
	const float windowPaddingBot;
	const float topPanelHeight;
	const float viewportWidth;
	const Vec2f viewportSize;
	const Vec2f viewportOffset;
	const sf::Rect<float> viewportRect;
	const Vec2f rightPannelPosition;

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

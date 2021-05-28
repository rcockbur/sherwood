#include "window_manager.h"
#include "map.h"
#include "entity.h"
#include "globals.h"

WindowManager::WindowManager(std::string windowName, uint targetFPS):
	lineWidthHalf(0.5),
	lineWidth (lineWidthHalf * 2),
	tileSize(24, 24),
	entitySize(20, 20),
	windowSize(800, 450),
	windowPaddingTop(5),
	windowPaddingLeft(5),
	windowPaddingBot(10),
	topPanelHeight(20),
	viewportWidth(580),
	viewportSize(viewportWidth, windowSize.y - windowPaddingTop - windowPaddingBot - topPanelHeight),
	viewportOffset(Vec2f(windowPaddingLeft, windowPaddingTop + topPanelHeight)),
	viewportRect(viewportOffset, viewportSize),
	rightPannelPosition(viewportOffset.x + viewportSize.x + 3, viewportOffset.y),
	mapView(sf::FloatRect(0, 0, viewportSize.x, viewportSize.y)),
	window(sf::VideoMode(windowSize.x, windowSize.y), windowName),
	targetFPS(targetFPS),
	actualFPS((float)targetFPS),
	gridSize(calculateGridSize(map.tileCount))
{
	window.setPosition(Vec2i(0, 0));
	window.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(viewportOffset.x / windowSize.x, viewportOffset.y / windowSize.y);
	Vec2f viewportSizeRatio(viewportSize.x / windowSize.x, viewportSize.y / windowSize.y);
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
}

Vec2f WindowManager::tileToWorld(const Vec2i tile) {
	return Vec2f(((float)tile.x + 0.5f) * tileSize.x, ((float)tile.y + 0.5f) * tileSize.y);
}

Vec2i WindowManager::worldToTile(const Vec2f pos) {
	return Vec2i((int)(pos.x / tileSize.x), (int)(pos.y / tileSize.y));
}

//0.5 ensures that the pixe
Vec2f WindowManager::screenToWorld(const Vec2f screenPos) {
	return window.mapPixelToCoords(Vec2i((int)(screenPos.x + 0.5f), (int)(screenPos.y + 0.5f)), mapView);
}

const Vec2f WindowManager::calculateGridSize(const Vec2i& tileCount) {
	return Vec2f(((float)tileCount.x) * tileSize.x, ((float)tileCount.y) * tileSize.y);
}
#include "window_manager.h"
#include "map.h"
#include "entity.h"
#include "globals.h"

WindowManager::WindowManager(std::string windowName, uint targetFPS):
	mapView(sf::FloatRect(0, 0, VIEWPORT_SIZE.x, VIEWPORT_SIZE.y)),
	window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), windowName),
	targetFPS(targetFPS),
	actualFPS((float)targetFPS),
	gridSize(calculateGridSize(map.tileCount))
{
	window.setPosition(Vec2i(0, 0));
	window.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(VIEWPORT_OFFSET.x / WINDOW_SIZE.x, VIEWPORT_OFFSET.y / WINDOW_SIZE.y);
	Vec2f viewportSizeRatio(VIEWPORT_SIZE.x / WINDOW_SIZE.x, VIEWPORT_SIZE.y / WINDOW_SIZE.y);
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
}

Vec2f WindowManager::tileToWorld(const Vec2i tile) {
	return Vec2f(((float)tile.x + 0.5f) * TILE_SIZE.x, ((float)tile.y + 0.5f) * TILE_SIZE.y);
}

Vec2i WindowManager::worldToTile(const Vec2f pos) {
	return Vec2i((int)(pos.x / TILE_SIZE.x), (int)(pos.y / TILE_SIZE.y));
}

Vec2f WindowManager::screenToWorld(const Vec2f screenPos) {
	return window.mapPixelToCoords(Vec2i((int)(screenPos.x + 0.5f), (int)(screenPos.y + 0.5f)), mapView);
}

const Vec2f WindowManager::calculateGridSize(const Vec2i& tileCount) {
	return Vec2f(((float)tileCount.x) * TILE_SIZE.x, ((float)tileCount.y) * TILE_SIZE.y);
}
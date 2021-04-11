#include "window_manager.h"
#include "map.h"

WindowManager::WindowManager(const Map& _map, std::string windowName, uint targetFPS):
	map(_map),
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
	return Vec2f((float)tile.x * tileSize.x, (float)tile.y * tileSize.y);
}

Vec2i WindowManager::worldToTile(const Vec2f pos) {
	return Vec2i((int)(pos.x / tileSize.x), (int)(pos.y / tileSize.y));
}

void WindowManager::handleScreenClick(const Vec2f position)
{
	std::cout << "ScreenPosition:" << position.x << "," << position.y << "\n";

	sf::Rect<float> viewportRect(viewportOffset, viewportSize + Vec2f(0, 0));

	if (viewportRect.contains(position)) {
		Vec2f worldPosition = window.mapPixelToCoords(Vec2i((int)(position.x + 0.5f), (int)(position.y + 0.5f)), mapView);
		handleWorldClick(worldPosition);
	}
	else {
		std::cout << "Out of bounds\n";
	}
}

void WindowManager::handleWorldClick(const Vec2f worldPosition)
{
	std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
	Vec2i clickedTile = worldToTile(worldPosition);
	std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
}

void WindowManager::updateFPS(uint fps)
{
	targetFPS = fps;
	window.setFramerateLimit(targetFPS);
}

const Vec2f WindowManager::calculateGridSize(const Vec2i& _tileCount) {
	return Vec2f(((float)_tileCount.x) * tileSize.x, ((float)_tileCount.y) * tileSize.y);
}
#include "input_manager.h"
#include "window_manager.h"
#include "map.h"
#include "entity.h"
#include "entity_manager.h"

InputManager::InputManager(Map& map, EntityManager& em, WindowManager& wm):
	map(map),
	wm(wm),
	em(em)
{

}

void InputManager::handleScreenClick(const Vec2f screenPos) {
	std::cout << "ScreenPosition:" << screenPos.x << "," << screenPos.y << "\n";

	if (viewportRect.contains(screenPos)) {
		Vec2f worldPos = wm.screenToWorld(screenPos);
		handleWorldClick(worldPos);
	}
	else {
		std::cout << "Out of bounds\n";
	}
}

void InputManager::handleWorldClick(const Vec2f worldPosition) {
	std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
	Vec2i clickedTile = wm.worldToTile(worldPosition);
	std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";

	Entity* entity = map.getEntityAt(clickedTile);
	if (entity != nullptr)
		em.selectEntity(entity);
}

void InputManager::updateFPS(uint fps) {
	wm.targetFPS = fps;
	wm.window.setFramerateLimit(wm.targetFPS);
}
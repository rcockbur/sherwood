#include "utility.h"
#include "map.h"

extern Vec2f cameraPos;
extern Map map;

Vec2f worldToScreen(const Vec2f world) {
	return world - cameraPos;
}

Vec2f tileToWorld(const Vec2i tile) {
	return Vec2f((float)tile.x * map.tileSize.x + map.lineWidthHalf, (float)tile.y * map.tileSize.y + map.lineWidthHalf);
}

Vec2f tileToScreen(const Vec2i tile) {
	return Vec2f((float)tile.x * map.tileSize.x - cameraPos.x + map.lineWidthHalf, 
		(float)tile.y * map.tileSize.y - cameraPos.y + map.lineWidthHalf);
}
#include "utility.h"
#include "globals.h"
#include "constants.h"

Vec2f tileToWorld(const Vec2i tile) {
	return Vec2f(((float)tile.x + 0.5f) * TILE_SIZE, ((float)tile.y + 0.5f) * TILE_SIZE);
}

Vec2i worldToTile(const Vec2f pos) {
	return Vec2i((int)(pos.x / TILE_SIZE), (int)(pos.y / TILE_SIZE));
}

Vec2f screenToWorld(const Vec2f screenPos) {
	return renderWindow.mapPixelToCoords(Vec2i((int)(screenPos.x + 0.5f), (int)(screenPos.y + 0.5f)), mapView);
}

Vec2f getTopLeft(const Vec2f center, const float size) {
	return center - Vec2f(size / 2, size / 2);
}
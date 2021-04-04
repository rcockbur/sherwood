#include "utility.h"
#include "map.h"

extern Map map;

Vec2f tileToWorld(const Vec2i tile) {
	return Vec2f((float)tile.x * map.tileSize.x + map.lineWidthHalf, (float)tile.y * map.tileSize.y + map.lineWidthHalf);
}

#include "utility.h"
#include "map.h"

//extern Vec2f cameraPos;
extern sf::View mapView;
extern Map map;

//Vec2f worldToScreen(const Vec2f world) {
//	return world;
//}

Vec2f tileToWorld(const Vec2i tile) {
	return Vec2f((float)tile.x * map.tileSize.x + map.lineWidthHalf, (float)tile.y * map.tileSize.y + map.lineWidthHalf);
}

//Vec2f tileToScreen(const Vec2i tile) {
//	return Vec2f((float)tile.x * map.tileSize.x + map.lineWidthHalf, 
//		(float)tile.y * map.tileSize.y + map.lineWidthHalf);
//}
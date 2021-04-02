#include "utility.h"

extern Vec2f cameraPos;

Vec2f worldToScreen(const Vec2f world) {
	return world - cameraPos;
}
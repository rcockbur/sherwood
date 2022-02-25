#pragma once
#include "types.h"

Vec2i worldToTile(const Vec2f worldPos);
Vec2f tileToWorld(const Vec2i tile);
Vec2f screenToWorld(const Vec2f screenPos);
Vec2f getTopLeft(const Vec2f center, const float size);
Entity* getEntityAtWorldPos(const Vec2f& worldPosition);
#pragma once
#include "globals.h"
#include "entity.h"
#include <vector>

class Map {
	Map(Vec2i);
	int getTerrainAt(Vec2i tile);
	Entity* getEntityAt(Vec2i tile);
	Vec2i tileCount;
	std::vector<std::vector<int>> terrain_grid;
	std::vector<std::vector<Entity *>> entity_grid;
};
#pragma once
#include <vector>
#include "globals.h"
#include "map.h"


class Entity;

class Map {
public:
	Map(std::string fileName);
	const Vec2i tileCount;
	std::vector<std::vector<int>> terrain_grid;
	std::vector<std::vector<Entity*>> entity_grid;

private:
	Vec2i calculateTileCount(std::string);
	void loadMapData(std::string);
};
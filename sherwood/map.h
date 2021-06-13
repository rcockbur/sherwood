#pragma once
#include "types.h"
#include <vector>

class Entity;

class Map {
public:
	Map(std::string fileName);
	const Vec2i tileCount;
	std::vector<std::vector<int>> terrainGrid;
	bool isWithinBounds(Vec2i tile);
	bool isPathable(Vec2i tile);
private:
	Vec2i calculateTileCount(std::string);
	void loadMapData(std::string);	
};
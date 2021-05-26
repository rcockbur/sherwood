#pragma once
#include "types.h"
#include <vector>

class Entity;

class Map {
public:
	Map(std::string fileName);
	const Vec2i tileCount;
	std::vector<std::vector<int>> terrainGrid;
	std::vector<std::vector<Entity*>> entityGrid;
	bool isWithinBounds(Vec2i tile);
	bool isPathable(Vec2i tile);
	Entity* getEntityAt(Vec2i tile);
private:
	Vec2i calculateTileCount(std::string);
	void loadMapData(std::string);	
};
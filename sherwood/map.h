#pragma once
#include "globals.h"
#include <vector>

class Entity;

class Map {
public:
	Map(std::string fileName);
	const Vec2i tileCount;
	std::vector<std::vector<int>> terrainGrid;
	std::vector<std::vector<Entity*>> entityGrid;
	Entity* getEntityAt(Vec2i tile);
private:
	Vec2i calculateTileCount(std::string);
	void loadMapData(std::string);	
};
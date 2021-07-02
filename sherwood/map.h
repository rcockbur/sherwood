#pragma once
#include "types.h"
#include <vector>

class Entity;

class Map {
public:
	Map(std::string fileName);
	const Vec2i tileCount;
	const Vec2f size;
	std::vector<std::vector<int>> terrainGrid;
	std::vector<std::vector<bool>> impassGrid;
	bool isWithinBounds(Vec2i tile);
	bool isPathable(Vec2i tile);
	void validateWithinBounds(const Vec2i tile) const;
	bool containsWorldPos(const Vec2f pos) const;
private:
	Vec2i calculateTileCount(std::string);
	void loadMapData(std::string);	
};
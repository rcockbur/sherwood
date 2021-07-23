#pragma once
#include "types.h"
#include <vector>
#include "lookup.h"
#include "entity.h"

class Entity;
class Fixed;

class Map {
public:
	Map(std::string fileName);
	const Vec2i tileCount;
	const Vec2f size;
	std::vector<std::vector<int>> terrainGrid;
	bool isWithinBounds(Vec2i tile) const;
	void validateWithinBounds(const Vec2i tile) const;
	bool containsWorldPos(const Vec2f pos) const;
	Fixed* getFixedFromTile(const Vec2i& tile) const;
	void setEntityAtTile(Fixed& fixedEntity, const Vec2i tile);
	void removeEntityAtTile(const Vec2i tile);
	template <typename T> T* lookupFixed(const Lookup) const;
	void validateStaticEntityGridAvailable(const Vec2i tile);

private:
	std::vector<std::vector<Fixed*>> fixedGrid;
	Vec2i calculateTileCount(std::string);
	void loadMapData(std::string);	
};

//if entity matches provided ID, then ptr is provided
template <typename T>
T* Map::lookupFixed(const Lookup lookup) const {
	if (fixedGrid[lookup.tile.x][lookup.tile.y] != nullptr) {
		if (fixedGrid[lookup.tile.x][lookup.tile.y]->id == lookup.id) {
			return dynamic_cast<T*>(fixedGrid[lookup.tile.x][lookup.tile.y]);
		}
	}
	return nullptr;
}

#pragma once
#include "types.h"
#include <vector>
#include "lookup.h"
#include "entity.h"

class Entity;

class Map {
public:
	Map(std::string fileName);
	const std::string fileName;
	const Vec2i tileCount;
	const Vec2f size;
	std::vector<std::vector<int>> terrainGrid;
	void setTerrainAtTile(const Vec2i tile, const int terrainType);
	bool isWithinBounds(Vec2i tile) const;
	void validateWithinBounds(const Vec2i tile) const;
	bool containsWorldPos(const Vec2f pos) const;
	Entity* getEntityFromTile(const Vec2i& tile) const;
	void setEntityAtTile(Entity& entity, const Vec2i tile);
	void removeEntityAtTile(const Vec2i tile);
	template <typename T> T* lookupEntity(const Lookup) const;
	void validateStaticEntityGridAvailable(const Vec2i tile);
	Entity* lookupEntity(const Lookup lookup) const;
	void saveMapData() const;
private:
	std::vector<std::vector<Entity*>> entityGrid;
	Vec2i calculateTileCount();
	void loadMapData();	
};
#include "map.h"

Map::Map(Vec2i _tileCount)
	: tileCount(_tileCount) {
	for (int x = 0; x < tileCount.x; x++) {
		for (int y = 0; y < tileCount.y; y++) {
			terrain_grid[x][y] = 0;
			entity_grid[x][y] = nullptr;
		}
	}
}

int Map::getTerrainAt(Vec2i tile) {
	return terrain_grid[tile.x][tile.y];
}

Entity* Map::getEntityAt(Vec2i tile) {
	return entity_grid[tile.x][tile.y];
}
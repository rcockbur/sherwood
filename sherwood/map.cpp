#include "map.h"
#include <iostream>

Map::Map(Vec2i _tileCount, Vec2f _tileSize, float _lineWidth, sf::Color _color)
	: tileCount(_tileCount), tileSize(_tileSize), color(_color), lineWidth(_lineWidth),
	lineWidthHalf(_lineWidth / 2), gridSize(calculateGridSize(_tileCount, _tileSize)) 
{
	std::cout << "Map created with size: " << tileCount.x << ", " << tileCount.y << "\n";
	terrain_grid.resize(tileCount.x);
	entity_grid.resize(tileCount.x);
	for (int x = 0; x < tileCount.x; x++) {
		terrain_grid[x].resize(tileCount.y);
		entity_grid[x].resize(tileCount.y);
		for (int y = 0; y < tileCount.y; y++) {
			terrain_grid[x][y] = 0;
			entity_grid[x][y] = nullptr;
		}
	}
	
}

Vec2f Map::calculateGridSize(const Vec2i& _tileCount, const Vec2f& _tileSize) {
	return Vec2f(((float)_tileCount.x) * _tileSize.x, ((float)_tileCount.y) * _tileSize.y);
}

//int Map::getTerrainAt(Vec2i tile) {
//	return terrain_grid[tile.x][tile.y];
//}
//
//Entity* Map::getEntityAt(Vec2i tile) {
//	return entity_grid[tile.x][tile.y];
//}
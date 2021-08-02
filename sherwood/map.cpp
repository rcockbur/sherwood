#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "map.h"
#include "constants.h"


Map::Map(std::string fileName) : 
	tileCount(calculateTileCount(fileName)),
	size((float)tileCount.x * TILE_SIZE, ((float)tileCount.y * TILE_SIZE))
{
	std::cout << "Map created with size " << tileCount.x << "," << tileCount.y << "\n";
	
	terrainGrid.resize(tileCount.x);
	entityGrid.resize(tileCount.x);
	for (int x = 0; x < tileCount.x; x++) {
		terrainGrid[x].resize(tileCount.y);
		entityGrid[x].resize(tileCount.y);
	}
	loadMapData("data/map.txt");
	
	std::cout << "Map data loaded\n";
}

bool Map::isWithinBounds(Vec2i tile) const {
	return (tile.x >= 0 && tile.x < tileCount.x&& tile.y >= 0 && tile.y < tileCount.y);
}

void Map::validateWithinBounds(const Vec2i tile) const {
	if (tile.x < 0 || tile.x >= tileCount.x || tile.y < 0 || tile.y >= tileCount.y)
		throw std::logic_error("tile is out of bounds");
}

Vec2i Map::calculateTileCount(std::string fileName) {
	std::ifstream inFile(fileName);
	int x = 0;
	int y = 0;
	int prevX = 0;
	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile, line)) {
			std::stringstream ss(line);
			std::string sym;
			x = 0;
			while (std::getline(ss, sym, ',')) {
				x++;
			}
			++y;
			if (x != prevX && prevX != 0)
				throw std::logic_error("map rows are of different sizes");
			prevX = x;
		}
	}
	return Vec2i(x, y);
}

void Map::loadMapData(std::string fileName) {
	std::ifstream inFile(fileName);
	int x = 0;
	int y = 0;
	if (inFile.is_open()) {
		std::string line;
		while (std::getline(inFile, line)) {
			std::stringstream ss(line);
			std::string sym;
			x = 0;
			while (std::getline(ss, sym, ',')) {
				terrainGrid[x][y] = std::stoi(sym);
				x++;
			}
			++y;
		}
	}
}

bool Map::containsWorldPos(const Vec2f pos) const {
	return (pos.x >= 0 && pos.x < size.x&& pos.y >= 0 && pos.y < size.y);
}

Entity* Map::getEntityFromTile(const Vec2i& tile) const {
	return entityGrid[tile.x][tile.y];
}

void Map::setEntityAtTile(Entity& entity, const Vec2i tile) {
	if (entityGrid[tile.x][tile.y])
		throw std::logic_error("entityGrid slot already occupied");
	entityGrid[tile.x][tile.y] = &entity;
}

void Map::removeEntityAtTile(const Vec2i tile) {
	if (entityGrid[tile.x][tile.y] == nullptr)
		throw std::logic_error("entityGrid slot already empty");
	entityGrid[tile.x][tile.y] = nullptr;
}

void Map::validateStaticEntityGridAvailable(const Vec2i tile) {
	if (entityGrid[tile.x][tile.y])
		throw std::logic_error("entityGrid slot already occupied");
}
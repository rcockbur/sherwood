#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "map.h"
#include "constants.h"
#include "globals.h"


Map::Map(std::string fileName) :
	fileName(fileName),
	tileCount(calculateTileCount()),
	size(calculateSize())
{
	std::cout << "Map created with size " << tileCount.x << "," << tileCount.y << "\n";
	
	terrainGrid.resize(tileCount.x);
	entityGrid.resize(tileCount.x);
	for (int x = 0; x < tileCount.x; x++) {
		terrainGrid[x].resize(tileCount.y);
		entityGrid[x].resize(tileCount.y);
	}
	loadMapData();
	
	std::cout << "Map data loaded\n";
}

Vec2f Map::calculateSize() {
	return Vec2f((float)tileCount.x * TILE_SIZE, (float)tileCount.y * TILE_SIZE);
}

void Map::setTerrainAtTile(const Vec2i tile, const int terrainType) {
	validateWithinBounds(tile);
	terrainGrid[tile.x][tile.y] = terrainType;
}

bool Map::isWithinBounds(Vec2i tile) const {
	return (tile.x >= 0 && tile.x < tileCount.x&& tile.y >= 0 && tile.y < tileCount.y);
}

void Map::validateWithinBounds(const Vec2i tile) const {
	if (tile.x < 0 || tile.x >= tileCount.x || tile.y < 0 || tile.y >= tileCount.y)
		throw std::logic_error("tile is out of bounds");
}

Vec2i Map::calculateTileCount() {
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

void Map::loadMapData() {
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

void Map::saveMapData() const {
	std::ofstream outFile(fileName, std::ofstream::trunc);
	if (outFile.is_open()) {
		for (int y = 0; y < tileCount.y; ++y) {
			for (int x = 0; x < tileCount.x; ++x) {
				outFile << std::to_string(terrainGrid[x][y]);
				if (x + 1 < tileCount.x) {
					outFile << ",";
				}
			}
			outFile << "\n";
		}
		outFile.close();
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

Entity* Map::lookupEntity(const Lookup lookup) const {
	if (entityGrid[lookup.tile.x][lookup.tile.y] != nullptr) {
		if (entityGrid[lookup.tile.x][lookup.tile.y]->id == lookup.id) {
			return entityGrid[lookup.tile.x][lookup.tile.y];
		}
	}
	return nullptr;
}

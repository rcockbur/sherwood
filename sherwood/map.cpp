#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "map.h"

Map::Map(std::string fileName)
	: tileCount(calculateTileCount(fileName))
{
	std::cout << "Map created with size " << tileCount.x << "," << tileCount.y << "\n";
	terrainGrid.resize(tileCount.x);
	for (int x = 0; x < tileCount.x; x++) {
		terrainGrid[x].resize(tileCount.y);
	}
	loadMapData("data/map.txt");
	std::cout << "Map data loaded\n";
}

bool Map::isWithinBounds(Vec2i tile) {
	return (tile.x >= 0 && tile.x < tileCount.x&& tile.y >= 0 && tile.y < tileCount.y);
}

bool Map::isPathable(Vec2i tile) {
	return (terrainGrid[tile.x][tile.y] == 0);
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

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
	terrain_grid.resize(tileCount.x);
	entity_grid.resize(tileCount.x);
	for (int x = 0; x < tileCount.x; x++) {
		terrain_grid[x].resize(tileCount.y);
		entity_grid[x].resize(tileCount.y);
	}
	loadMapData("data/map.txt");
	std::cout << "Map data loaded\n";
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
				terrain_grid[x][y] = std::stoi(sym);
				entity_grid[x][y] = nullptr;
				x++;
			}
			++y;
		}
	}
}

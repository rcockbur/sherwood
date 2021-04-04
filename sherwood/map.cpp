#include "map.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

extern Colors colors;

Map map("data/map.txt", { 15., 15. }, 1., colors.grey);

Map::Map(std::string fileName, Vec2f _tileSize, float _lineWidth, sf::Color _color)
	: tileCount(calculateTileCount(fileName)), tileSize(_tileSize), color(_color), lineWidth(_lineWidth),
	lineWidthHalf(_lineWidth / 2), gridSize(calculateGridSize(tileCount, _tileSize))
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

Vec2f Map::calculateGridSize(const Vec2i& _tileCount, const Vec2f& _tileSize) {
	return Vec2f(((float)_tileCount.x) * _tileSize.x, ((float)_tileCount.y) * _tileSize.y);
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

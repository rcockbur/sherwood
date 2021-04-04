#pragma once
#include "globals.h"
#include "entity.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Map {
public:
	Map(std::string fileName, Vec2f tileSize, float lineWidth, sf::Color color);
	//int getTerrainAt(Vec2i tile);
	//Entity* getEntityAt(Vec2i tile);
	const Vec2i tileCount;
	const Vec2f tileSize;
	const Vec2f gridSize;
	const float lineWidth;
	const float lineWidthHalf;
	const sf::Color color;
	std::vector<std::vector<int>> terrain_grid;
	std::vector<std::vector<Entity*>> entity_grid;
private:
	Vec2f calculateGridSize(const Vec2i& tileCount, const Vec2f& tileSize);
	Vec2i calculateTileCount(std::string);
	void loadMapData(std::string);
	
};
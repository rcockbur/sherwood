#pragma once
#include "globals.h"
#include "entity.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Map {
public:
	Map(Vec2i tileCount, Vec2f tileSize, float lineWidth, sf::Color color);
	//int getTerrainAt(Vec2i tile);
	//Entity* getEntityAt(Vec2i tile);
	const Vec2i tileCount;
	const Vec2f tileSize;
	const Vec2f gridSize;
	const float lineWidth;
	const sf::Color color;
	std::vector<std::vector<int>> terrain_grid;
	std::vector<std::vector<Entity *>> entity_grid;
private:
	Vec2f calculateGridSize(const Vec2i& tileCount, const Vec2f& tileSize);
};
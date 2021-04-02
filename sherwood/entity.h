#pragma once
#include "globals.h"
#include "entity_type.h"
#include <SFML/Graphics.hpp>

struct Entity {
	unsigned int id;
	EntityType* type;
	Vec2i tile;
	sf::Color color;
	Entity(EntityType* , unsigned int, Vec2i);
	void update();
	void draw();
};


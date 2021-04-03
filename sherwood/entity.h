#pragma once
#include <vector>
#include "globals.h"
#include "entity_type.h"
#include "ability.h"
#include <SFML/Graphics.hpp>


class Entity {
public:
	uint id;
	EntityType* type;
	Vec2i tile;
	sf::Color color;
	std::vector<Ability*> abilityQueue;
	uint canMoveAt;
	Entity(EntityType* _type, uint _id, const Vec2i& _tile);
	void update();
	void addAbility(Ability* ability);
};


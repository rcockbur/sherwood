#pragma once
#include "types.h"
class FixedEntity;
class Entity;

class Lookup {
public:
	int id;
	Vec2i tile;
	Lookup();
	Lookup(const int, const Vec2i);
	Lookup(const FixedEntity& fixedEntity);
	void operator=(const FixedEntity& fixedEntity);
	bool operator==(const Entity& fixedEntity);
};
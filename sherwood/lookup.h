#pragma once
#include "types.h"
//class Fixed;
class Entity;

class Lookup {
public:
	int id;
	Vec2i tile;
	Lookup();
	Lookup(const int, const Vec2i);
	Lookup(const Entity& entity);
	void operator=(const Entity& entity);
	bool operator==(const Entity& entity);
};
#pragma once
#include "types.h"
class Fixed;
class Entity;

class Lookup {
public:
	int id;
	Vec2i tile;
	Lookup();
	Lookup(const int, const Vec2i);
	Lookup(const Fixed& fixedEntity);
	void operator=(const Fixed& fixedEntity);
	bool operator==(const Entity& fixedEntity);
};
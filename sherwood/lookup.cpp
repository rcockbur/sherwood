#include "lookup.h"
#include "entity.h"

Lookup::Lookup() :
	id(-1)
{

}

Lookup::Lookup(const int id, const Vec2i tile) :
	id(id),
	tile(tile)
{}

Lookup::Lookup(const Entity& entity) :
	id(entity.id),
	tile(entity.tile)
{}

void Lookup::operator=(const Entity& entity) {
	id = entity.id;
	tile = entity.tile;
}

bool Lookup::operator==(const Entity& fixedEntity) {
	return (id == fixedEntity.id);
}
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

Lookup::Lookup(const FixedEntity& fixedEntity) :
	id(fixedEntity.id),
	tile(fixedEntity.tile)
{}

void Lookup::operator=(const FixedEntity& fixedEntity) {
	id = fixedEntity.id;
	tile = fixedEntity.tile;
}

bool Lookup::operator==(const Entity& fixedEntity) {
	return (id == fixedEntity.id);
}
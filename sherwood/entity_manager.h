#pragma once
#include "types.h"
#include <unordered_map>
#include <set>
#include "entity.h"
#include "lookup.h"

class EntityManager {
public:
	EntityManager();
	void updateEntities();
	void selectEntity(Entity*);
	void deselectEntity(Entity*);
	Entity* getEntityAtWorldPos(const Vec2f& worldPosition) const;
	FixedEntity* getEntityFromTile(const Vec2i& tile) const;
	template <typename T> T lookupFixedEntity(const Lookup) const;
	Unit* getUnitByID(const int id) const;
	std::set<Entity*> entities;
	std::unordered_map<int, Unit*> unitMap;
	std::vector<std::vector<FixedEntity*>> staticEntityGrid; //does not include units
	void validateStaticEntityGridAvailable(const Vec2i tile);
};

//if entity matches provided ID, then ptr is provided
template <typename T>
T EntityManager::lookupFixedEntity(const Lookup lookup) const {
	if (staticEntityGrid[lookup.tile.x][lookup.tile.y] != nullptr) {
		if(staticEntityGrid[lookup.tile.x][lookup.tile.y]->id == lookup.id) {
			return dynamic_cast<T>(staticEntityGrid[lookup.tile.x][lookup.tile.y]);
		}
	}
	return nullptr;
}
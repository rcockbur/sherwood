#include "ability.h"
#include "entity.h"
#include "entity_type.h"
#include "globals.h"

Move::Move(Unit& unit, std::list<Vec2i> _path)
	: unit(unit), path(_path)
{

}

bool Move::execute() {
	if (path.empty()) {
		return true;
	}
	else {
		followPath();
		return false;
	}
}

void Move::followPath() {
	if (path.size() > 0) {
		if (tic >= unit.canMoveAt) {
			unit.canMoveAt = tic + unit.type.movePeriod;
			bool hasReachedTile = unit.moveTowards(path.front());
			if (hasReachedTile)
				path.pop_front();
		}
	}
}

Harvest::Harvest(Unit& unit, std::list<Vec2i> path, Deposit& _source, int _resourceType) :
	Move(unit, path),
	source(_source),
	resourceType(_resourceType)
{

}

bool Harvest::execute() {
	if (path.empty()) {
		//Resources diff = unit.resources
		return true;
	}
	else {
		followPath();
		return false;
	}
}
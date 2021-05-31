#include "ability.h"
#include "entity.h"
#include "entity_type.h"

extern uint tic;

Move::Move(Unit& unit, std::list<Vec2i> _path)
	: unit(unit), path(_path)
{

}

bool Move::execute() 
{
	if (path.size() > 0) {
		if (tic >= unit.canMoveAt) {
			unit.canMoveAt = tic + unit.type.movePeriod;
			bool hasReachedTile = unit.moveTowards(path.front());
			if (hasReachedTile)
				path.pop_front();
		}
	}
	return path.empty();
}

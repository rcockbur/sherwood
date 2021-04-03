#include "globals.h"
#include "ability.h"
#include <list>
#include "entity.h"

extern uint tic;

Move::Move(Entity& _entity, std::list<Vec2i> _path) 
	: entity(_entity), path(_path)
{

}

bool Move::execute() 
{
	if (path.size() > 0) {
		if (tic >= entity.canMoveAt) {
			entity.canMoveAt = tic + entity.type->movePeriod;
			entity.tile = path.front();
			path.pop_front();
		}
	}
	return path.empty();
}

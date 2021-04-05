#include "ability.h"
#include "entity.h"
#include "entity_type.h"

extern uint tic;

Move::Move(Entity& _entity, std::list<Vec2i> _path) 
	: entity(_entity), path(_path)
{

}

bool Move::execute() 
{
	if (path.size() > 0) {
		if (tic >= entity.canMoveAt) {
			entity.canMoveAt = tic + entity.type.movePeriod;
			entity.move(path.front());
			path.pop_front();
		}
	}
	return path.empty();
}

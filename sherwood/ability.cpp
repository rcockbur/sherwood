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

Harvest::Harvest(Unit& unit, std::list<Vec2i> path, Deposit& _deposit) :
	Move(unit, path),
	deposit(_deposit),
	hasReachedDeposit(false)
{

}

bool Harvest::execute() {
	if (hasReachedDeposit) {
		if (unit.carryAmmount == unit.type.carryCapacity || deposit.amount == 0) {
			return true; //done gathering
		}
		else {
			if (tic >= unit.canGatherAt) {
				++unit.carryAmmount;
				--deposit.amount;
				unit.canGatherAt = tic + unit.type.gatherPeriod;
			}
			return false; //not done gathering
		}
	}
	else {
		followPath();
		if (path.empty()) {
			hasReachedDeposit = true;
			unit.canGatherAt = tic + unit.type.gatherPeriod;
			if (unit.carryType != deposit.type.resourceType) {
				unit.carryType = deposit.type.resourceType;
				unit.carryAmmount = 0;
			}
			
		}
		
		return false; //not done moving
		
	}
}

ReturnResources::ReturnResources(Unit& unit, std::list<Vec2i> path) :
	Move(unit, path)
{}

bool ReturnResources::execute() {
	if (path.empty()) {
		unit.home->resources[unit.carryType] += unit.carryAmmount;
		unit.carryAmmount = 0;
		return true;
	}
	else {
		followPath();
		return false;
	}
}
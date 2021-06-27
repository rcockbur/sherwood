#include "ability.h"
#include "entity.h"
#include "entity_type.h"
#include "globals.h"
#include "pathfinding.h"

Move::Move(Unit& unit, const Vec2i dest)
	: unit(unit), dest(dest), hasStarted(false), stopShort(false)
{

}

Status Move::execute() {
	if (hasStarted == false) {
		hasStarted = true;
		if (astar.search(unit.tile, dest)) {
			path = astar.path(stopShort);
		}
		else {
			return failure;
		}
	}
	if (path.empty()) {
		return success;
	}
	else {
		followPath();
		return inProgress;
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

Harvest::Harvest(Unit& unit, const Lookup depositLookup) :
	Move(unit, depositLookup.tile),
	depositLookup(depositLookup),
	hasStartedHarvesting(false)
	
{
	stopShort = true;
}

Status Harvest::execute() {
	if (hasStarted == false) {
		hasStarted = true;
		if (astar.search(unit.tile, dest)) {
			path = astar.path(stopShort);
		}
		else {
			return failure;
		}
	}
	if (path.empty()) {
		if (tic >= unit.canGatherAt) {
			Deposit* deposit = em.lookupFixedEntity<Deposit*>(depositLookup);
			if (deposit == nullptr) {
				if (hasStartedHarvesting) {
					return success; //deposit destroyed while gathering
				}
				else {
					return failure; //deposit destroyed before reached
				}
			}
			if (hasStartedHarvesting == false) {
				hasStartedHarvesting = true;
				if (unit.carryType != deposit->type.resourceType) {
					unit.carryType = deposit->type.resourceType;
					unit.carryAmmount = 0;
				}
			}
			++unit.carryAmmount;
			--deposit->amount;
			unit.canGatherAt = tic + unit.type.gatherPeriod;
			if (deposit->amount == 0) {
				delete deposit;
				return success; //deposit has expired
			}
			if (unit.carryAmmount == unit.type.carryCapacity) {
				return success; //done gathering
			}
		}
		return inProgress; //still gathering
	}

	else {
		followPath();
		if (path.empty()) {
			unit.canGatherAt = tic + unit.type.gatherPeriod;
		}
		return inProgress; //still moving
	}

}

ReturnResources::ReturnResources(Unit& unit, const Lookup buildingLookup) :
	Move(unit, buildingLookup.tile)
{
	stopShort = true;
}

Status ReturnResources::execute() {
	if (hasStarted == false) {
		hasStarted = true;
		if (astar.search(unit.tile, dest)) {
			path = astar.path(stopShort);
		}
		else {
			return failure;
		}
	}
	if (path.empty()) {
		Building* home = em.lookupFixedEntity<Building*>(unit.homeLookup);
		home->resources[unit.carryType] += unit.carryAmmount;
		unit.carryAmmount = 0;
		return success;
	}
	else {
		followPath();
		return inProgress;
	}
}
#include "ability.h"
#include "entity.h"
#include "entity_type.h"
#include "globals.h"
#include "pathfinding.h"

Move::Move(Unit& unit, Vec2i dest, std::list<Vec2i>&& path) : 
	unit(unit), 
	dest(dest), 
	path(path)
{}

ActivityStatus Move::execute() {
	if (path.empty()) {
		return ActivityStatus::success;
	}
	else {
		followPath();
		return ActivityStatus::inProgress;
	}
}

void Move::followPath() {
	if (path.size() > 0) {
		if (tics >= unit.canMoveAt) {
			unit.canMoveAt = tics + unit.unitType().movePeriod;
			bool hasReachedTile = unit.moveTowards(path.front());
			if (hasReachedTile)
				path.pop_front();
		}
	}
}

Harvest::Harvest(Unit& unit, Lookup depositLookup, std::list<Vec2i>&& path) :
	Move(unit, depositLookup.tile, std::move(path)),
	depositLookup(depositLookup),
	hasStartedHarvesting(false)
{}

ActivityStatus Harvest::execute() {
	if (path.empty()) {
		if (tics >= unit.canGatherAt) {
			Deposit* deposit = em.lookupFixedEntity<Deposit*>(depositLookup);
			if (deposit == nullptr) {
				if (hasStartedHarvesting) {
					return ActivityStatus::success; //deposit destroyed while gathering
				}
				else {
					return ActivityStatus::failure; //deposit destroyed before reached
				}
			}
			if (hasStartedHarvesting == false) {
				hasStartedHarvesting = true;
				if (unit.carryType != deposit->depositType().resourceType) {
					unit.carryType = deposit->depositType().resourceType;
					unit.carryAmmount = 0;
				}
			}
			if (unit.carryAmmount >= unit.unitType().carryCapacity) {
				return ActivityStatus::success; //done gathering
			}
			++unit.carryAmmount;
			--deposit->amount;
			unit.canGatherAt = tics + unit.unitType().gatherPeriod;
			if (deposit->amount == 0) {
				delete deposit;
				return ActivityStatus::success; //deposit has expired
			}
			
		}
		return ActivityStatus::inProgress; //still gathering
	}
	else {
		followPath();
		return ActivityStatus::inProgress; //still moving
	}

}

ReturnResources::ReturnResources(Unit& unit, Lookup buildingLookup, std::list<Vec2i>&& path) :
	Move(unit, buildingLookup.tile, std::move(path)),
	houseLookup(buildingLookup)
{}



ActivityStatus ReturnResources::execute() {
	if (path.empty()) {
		Building* home = em.lookupFixedEntity<Building*>(houseLookup);
		if (home) {
			home->resources[unit.carryType] += unit.carryAmmount;
			unit.carryAmmount = 0;
			return ActivityStatus::success;
		}
		else 
			return ActivityStatus::failure;
	}
	else {
		followPath();
		return ActivityStatus::inProgress;
	}
}
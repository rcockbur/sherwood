#include "ability.h"
#include "entity.h"
#include "entity_type.h"
#include "globals.h"
#include "pathfinding.h"

Move::Move(Unit& unit, Vec2i dest)
	: unit(unit), dest(dest), hasStarted(false)
{}

ActivityStatus Move::start() {
	hasStarted = true;
	if (aStar.searchForTile(unit.tile, dest)) {
			path = aStar.path();
		return ActivityStatus::success;
	}
	else {
		return ActivityStatus::failure;
	}
}

ActivityStatus Move::execute() {
	if (hasStarted == false) {
		ActivityStatus startStatus = start();
		if (startStatus == ActivityStatus::failure)
			return ActivityStatus::failure;
	}
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

Harvest::Harvest(Unit& unit, Lookup depositLookup) :
	Move(unit, depositLookup.tile),
	depositLookup(depositLookup),
	hasStartedHarvesting(false)
	
{}

ActivityStatus Harvest::start() {
	hasStarted = true;
	if (aStar.searchForTile(unit.tile, dest)) {
		path = aStar.path();
		return ActivityStatus::success;
	}
	else {
		return ActivityStatus::failure;
	}
}

ActivityStatus Harvest::execute() {
	if (hasStarted == false) {
		ActivityStatus startStatus = start();
		if (startStatus == ActivityStatus::failure)
			return ActivityStatus::failure;
	}
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

ReturnResources::ReturnResources(Unit& unit, Lookup buildingLookup) :
	Move(unit, buildingLookup.tile),
	pathProvidedByFloodfill(false)
{}

ReturnResources::ReturnResources(Unit& unit, Lookup buildingLookup, std::list<Vec2i> _path) :
	Move(unit, buildingLookup.tile),
	pathProvidedByFloodfill(true),
	houseLookup(buildingLookup)
{
	path = _path;
}

ActivityStatus ReturnResources::start() {
	hasStarted = true;
	if (pathProvidedByFloodfill) {
		return ActivityStatus::success;
	}
	else if (aStar.searchForTile(unit.tile, dest)) {
		path = aStar.path();
		return ActivityStatus::success;
	}
	else {
		return ActivityStatus::failure;
	}
}

ActivityStatus ReturnResources::execute() {
	if (hasStarted == false) {
		ActivityStatus startStatus = start();
		if (startStatus == ActivityStatus::failure)
			return ActivityStatus::failure;
	}
	if (path.empty()) {
		Building* home = em.lookupFixedEntity<Building*>(houseLookup);
		//if(em.getEntityAtWorldPos)
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
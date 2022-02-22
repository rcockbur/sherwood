#include "ability.h"
#include "entity.h"
#include "entity_style.h"
#include "globals.h"

Move::Move(Entity& unit, Vec2i dest, std::list<Vec2i>&& path) :
	unit(unit), 
	dest(dest), 
	path(path)
{}

ActivityStatus Move::execute(bool isLastJob) {
	ActivityStatus r;
	if (path.empty()) {
		r = ActivityStatus::success;
	}
	else {
		followPath();
		r = ActivityStatus::inProgress;
	}
	return r;
}

void Move::followPath() {
	if (path.size() > 0) {
		if (tics >= unit.canMoveAt) {
			if (unit.tileIsPathable(path.front())) {
				unit.canMoveAt = tics + unit.style.movePeriod;
				bool hasReachedTile = unit.moveTowards(path.front());
				if (hasReachedTile)
					path.pop_front();
			}
		}
	}
}

Harvest::Harvest(Entity& unit, Lookup depositLookup, std::list<Vec2i>&& path) :
	Move(unit, depositLookup.tile, std::move(path)),
	depositLookup(depositLookup),
	hasStartedHarvesting(false)
{}

ActivityStatus Harvest::execute(bool isLastJob) {
	ActivityStatus r;
	if (path.empty()) {
		if (tics >= unit.canGatherAt) {
			Entity* deposit = map.lookupEntity(depositLookup);
			if (deposit == nullptr) {
				if (hasStartedHarvesting) {
					r = ActivityStatus::success; //deposit destroyed while gathering
				}
				else {
					r = ActivityStatus::failure; //deposit destroyed before reached
				}
			}
			else {
				if (hasStartedHarvesting == false) {
					hasStartedHarvesting = true;
					if (unit.carryType != deposit->style.resourceType) {
						unit.carryType = deposit->style.resourceType;
						unit.carryAmmount = 0;
					}
				}
				if (unit.carryAmmount >= unit.style.carryCapacity) {
					r = ActivityStatus::success; //done gathering
				}
				else {
					++unit.carryAmmount;
					--deposit->amount;
					unit.canGatherAt = tics + unit.style.gatherPeriod;
					if (deposit->amount == 0) {
						delete deposit;
						r = ActivityStatus::success; //deposit has expired
					}
					else {
						r = ActivityStatus::inProgress; //still gathering
					}
				}
			}
		}
		else {
			r = ActivityStatus::inProgress; //waiting to gather
		}
	}
	else {
		followPath();
		r = ActivityStatus::inProgress; //still moving
	}
	return r;
}

ReturnResources::ReturnResources(Entity& unit, Lookup buildingLookup, std::list<Vec2i>&& path) :
	Move(unit, buildingLookup.tile, std::move(path)),
	houseLookup(buildingLookup)
{}

ActivityStatus ReturnResources::execute(bool isLastJob) {
	ActivityStatus r;
	if (path.empty()) {
		Entity* home = map.lookupEntity(houseLookup);
		if (home) {
			home->resources[unit.carryType] += unit.carryAmmount;
			unit.carryAmmount = 0;
			r = ActivityStatus::success;
		}
		else 
			r = ActivityStatus::failure;
	}
	else {
		followPath();
		r = ActivityStatus::inProgress;
	}
	return r;
}

Garrison::Garrison(Entity& unit, Lookup buildingLookup, std::list < Vec2i>&& path) :
	Move(unit, buildingLookup.tile, std::move(path)),
	buildingLookup(buildingLookup)
{}

ActivityStatus Garrison::execute(bool isLastJob) {
	ActivityStatus r;
	if (path.empty()) {
		Entity* building = map.lookupEntity(buildingLookup);
		if (building) {
			unit.garrison(*building);
			r = ActivityStatus::success;
		}
		else
			r = ActivityStatus::failure;
	}
	else {
		followPath();
		r = ActivityStatus::inProgress;
	}
	return r;
}
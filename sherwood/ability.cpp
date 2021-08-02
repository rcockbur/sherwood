#include "ability.h"
#include "entity.h"
#include "entity_style.h"
#include "globals.h"

Move::Move(Unit& unit, Vec2i dest, std::list<Vec2i>&& path) : 
	unit(unit), 
	dest(dest), 
	path(path)
	//atFinalTile(false)
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
	/*if (atFinalTile == false && path.size() <= 1) {*/
	//if (atFinalTile == false && unit.tile == path.back()) {
	//	atFinalTile = true;
	//	if (isLastJob) {
	//		map.setEntityAtTile(unit, unit.tile);
	//	}
	//}
	return r;
}

void Move::followPath() {
	if (path.size() > 0) {
		if (tics >= unit.canMoveAt) {
			if (unit.tileIsPathable(path.front())) {
				//bool blockImpass = blockImpassAtEnd && path.size() == 1;
				unit.canMoveAt = tics + unit.unitStyle().movePeriod;
				bool hasReachedTile = unit.moveTowards(path.front());
				if (hasReachedTile)
					path.pop_front();
			}
		}
	}
}

Harvest::Harvest(Unit& unit, Lookup depositLookup, std::list<Vec2i>&& path) :
	Move(unit, depositLookup.tile, std::move(path)),
	depositLookup(depositLookup),
	hasStartedHarvesting(false)
{}

ActivityStatus Harvest::execute(bool isLastJob) {
	ActivityStatus r;
	if (path.empty()) {
		if (tics >= unit.canGatherAt) {
			Deposit* deposit = map.lookupEntity<Deposit>(depositLookup);
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
					if (unit.carryType != deposit->depositStyle().resourceType) {
						unit.carryType = deposit->depositStyle().resourceType;
						unit.carryAmmount = 0;
					}
				}
				if (unit.carryAmmount >= unit.unitStyle().carryCapacity) {
					r = ActivityStatus::success; //done gathering
				}
				else {
					++unit.carryAmmount;
					--deposit->amount;
					unit.canGatherAt = tics + unit.unitStyle().gatherPeriod;
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
	/*if (atFinalTile == false && path.size() <= 1) {*/
	//if (atFinalTile == false && unit.tile == path.back()) {
	//	atFinalTile = true;
	//	map.setEntityAtTile(unit, unit.tile);
	//}
	return r;
}

ReturnResources::ReturnResources(Unit& unit, Lookup buildingLookup, std::list<Vec2i>&& path) :
	Move(unit, buildingLookup.tile, std::move(path)),
	houseLookup(buildingLookup)
{}

ActivityStatus ReturnResources::execute(bool isLastJob) {
	ActivityStatus r;
	if (path.empty()) {
		Building* home = map.lookupEntity<Building>(houseLookup);
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
	/*if (atFinalTile == false && path.size() <= 1) {*/
	//if (atFinalTile == false && unit.tile == path.back()) {
	//	atFinalTile = true;
	//	if (isLastJob) {
	//		map.setEntityAtTile(unit, unit.tile);
	//	}
	//}
	return r;
}
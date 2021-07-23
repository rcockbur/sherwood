#include "job.h"
#include "ability.h"
#include "entity_style.h"
#include "globals.h"
#include "pathfinding.h"

Job::Job(Unit& _unit) :
	unit(_unit),
	hasStarted(false),
	ability(nullptr)
{}

ActivityStatus Job::start() {
	hasStarted = true;
	checkForAnotherAbility();
	if (ability == nullptr)
		return ActivityStatus::failure;
	return ActivityStatus::success;
}

CompleteStatus Job::execute() {
	if (hasStarted == false) {
		if (start() == ActivityStatus::failure) {
			ability.reset();
			return CompleteStatus::complete;
		}
	}
	ActivityStatus abilityStatus = ability->execute();
	switch (abilityStatus) {
	case(ActivityStatus::inProgress):
		return CompleteStatus::incomplete;
	default:
		ability.reset();
		checkForAnotherAbility();
		if (ability == nullptr)
			return CompleteStatus::complete;
		else
			return CompleteStatus::incomplete;
	}
}

Harvester::Harvester(Unit& _unit, const Lookup depositLookup) :
	Job(_unit),
	depositLookup(depositLookup),
	forcedHarvest(true)
{}

void Harvester::checkForAnotherAbility() {
	if (forcedHarvest == true || unit.carryAmmount == 0) {
		Deposit* deposit = map.lookupFixed<Deposit>(depositLookup);
		if (deposit != nullptr) {
			forcedHarvest = false;
			if (aStar.search(unit.tile, deposit->tile, unit.unitType().pathableTypes)) {
				std::list<Vec2i>path = aStar.path();
				ability.reset(new Harvest(unit, depositLookup, std::move(path)));
			}
		}
	}
	else {
		Fixed* targetHouse = breadthFirst.search(unit.tile, house, unit.unitType().pathableTypes);
		if (targetHouse) {
			Lookup houseLookup = Lookup(*targetHouse);
			std::list<Vec2i> path = breadthFirst.path();
			ability.reset(new ReturnResources(unit, houseLookup, std::move(path)));
		}
	}
}

Mover::Mover(Unit& _unit, const Vec2i targetTile) :
	Job(_unit),
	targetTile(targetTile)
{}

void Mover::checkForAnotherAbility() {
	if (unit.tile != targetTile) {
		if (aStar.search(unit.tile, targetTile, unit.unitType().pathableTypes)) {
			std::list<Vec2i> path = aStar.path();
			ability.reset(new Move(unit, targetTile, std::move(path)));
		}
		
	}
}
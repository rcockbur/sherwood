#include "job.h"
#include "ability.h"
#include "entity_type.h"
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
		Deposit* deposit = em.lookupFixedEntity<Deposit*>(depositLookup);
		if (deposit != nullptr) {
			forcedHarvest = false;
			if (aStar.searchForTile(unit.tile, deposit->tile)) {
				std::list<Vec2i>path = aStar.path();
				ability.reset(new Harvest(unit, depositLookup, std::move(path)));
			}
		}
	}
	else {
		FixedEntity* targetHouse = newBreadthFirst.searchForFixedEntityType(unit.tile, house);
		if (targetHouse) {
			Lookup houseLookup = Lookup(*targetHouse);
			std::list<Vec2i> path = newBreadthFirst.path();
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
		if (aStar.searchForTile(unit.tile, targetTile)) {
			std::list<Vec2i> path = aStar.path();
			ability.reset(new Move(unit, targetTile, std::move(path)));
		}
		
	}
}
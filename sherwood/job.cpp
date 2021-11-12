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

CompleteStatus Job::execute(bool isLastJob) {
	if (hasStarted == false) {
		if (start() == ActivityStatus::failure) {
			ability.reset();
			return CompleteStatus::complete;
		}
	}
	ActivityStatus abilityStatus = ability->execute(isLastJob);
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

Harvester::Harvester(Unit& _unit, Deposit& deposit) :
	Job(_unit),
	depositLookup(deposit),
	forcedHarvest(true),
	depositEntityStyle(deposit.depositStyle())
{}

void Harvester::checkForAnotherAbility() {
	if (forcedHarvest == true || unit.carryAmmount == 0) {
		forcedHarvest = false;
		Deposit* deposit = map.lookupEntity<Deposit>(depositLookup);
		if (deposit) {
			if (aStar.search(unit.tile, deposit->tile, unit.unitStyle().pathableTypes)) {
				std::list<Vec2i>path = aStar.path();
				ability.reset(new Harvest(unit, depositLookup, std::move(path)));
			}
		}
		else {
			Entity* entity = breadthFirst.search(depositLookup.tile, depositEntityStyle, unit.unitStyle().pathableTypes);
			if (entity) {
				deposit = static_cast<Deposit*>(entity);
				depositLookup = Lookup(*deposit);
				if (aStar.search(unit.tile, deposit->tile, unit.unitStyle().pathableTypes)) {
					std::list<Vec2i>path = aStar.path();
					ability.reset(new Harvest(unit, depositLookup, std::move(path)));
				}
			}
		}
	}
	else {
		Entity* dropoff = breadthFirst.search(unit.tile, MILL, unit.unitStyle().pathableTypes);
		if (dropoff) {
			Lookup houseLookup = Lookup(*dropoff);
			std::list<Vec2i> path = breadthFirst.path();
			ability.reset(new ReturnResources(unit, houseLookup, std::move(path)));
		}
	}
}

Mover::Mover(Unit& _unit, const Vec2i _targetTile) :
	Job(_unit),
	targetTile(_targetTile)
{
	int a = 2;
}

void Mover::checkForAnotherAbility() {
	if (unit.tile != targetTile) {
		if (aStar.search(unit.tile, targetTile, unit.unitStyle().pathableTypes)) {
			std::list<Vec2i> path = aStar.path();
			ability.reset(new Move(unit, targetTile, std::move(path)));
		}
		
	}
}

Idler::Idler(Unit& _unit) :
	Job(_unit),
	idleSince(tics)
{

}

void Idler::checkForAnotherAbility() {
	if (tics - idleSince > 200) {
		idleSince = tics;

	}
}
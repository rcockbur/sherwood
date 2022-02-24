#include "job.h"
#include "ability.h"
#include "entity_style.h"
#include "globals.h"
#include "pathfinding.h"

Job::Job(Entity& _unit) :
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

std::list<Vec2i>* Job::getPath() {
	if (ability != nullptr) {
		return ability->getPath();
	}
	return nullptr;
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

Harvester::Harvester(Entity& _unit, Entity& deposit) :
	Job(_unit),
	depositLookup(deposit),
	forcedHarvest(true),
	depositEntityStyle(deposit.style)
{}

void Harvester::checkForAnotherAbility() {
	if (forcedHarvest == true || unit.carryAmmount == 0) {
		forcedHarvest = false;
		Entity* deposit = map.lookupEntity(depositLookup);
		if (deposit) {
			if (aStar.search(unit.tile, deposit->tile, unit.style.pathableTypes)) {
				std::list<Vec2i>path = aStar.path();
				ability.reset(new Harvest(unit, depositLookup, std::move(path)));
			}
		}
		else {
			Entity* entity = breadthFirst.search(depositLookup.tile, depositEntityStyle, unit.style.pathableTypes);
			if (entity) {
				deposit = static_cast<Entity*>(entity);
				depositLookup = Lookup(*deposit);
				if (aStar.search(unit.tile, deposit->tile, unit.style.pathableTypes)) {
					std::list<Vec2i>path = aStar.path();
					ability.reset(new Harvest(unit, depositLookup, std::move(path)));
				}
			}
		}
	}
	else {
		Entity* dropoff = breadthFirst.search(unit.tile, MILL, unit.style.pathableTypes);
		if (dropoff) {
			Lookup houseLookup = Lookup(*dropoff);
			std::list<Vec2i> path = breadthFirst.path();
			ability.reset(new ReturnResources(unit, houseLookup, std::move(path)));
		}
	}
}

Mover::Mover(Entity& _unit, const Vec2i _targetTile) :
	Job(_unit),
	targetTile(_targetTile)
{
	int a = 2;
}

void Mover::checkForAnotherAbility() {
	if (unit.tile != targetTile) {
		if (aStar.search(unit.tile, targetTile, unit.style.pathableTypes)) {
			std::list<Vec2i> path = aStar.path();
			ability.reset(new Move(unit, targetTile, std::move(path)));
		}
		
	}
}

Garrisoner::Garrisoner(Entity& _unit, Entity& target) :
	Job(_unit),
	targetLookup(target)
{}

void Garrisoner::checkForAnotherAbility() {
	Entity* building = map.lookupEntity(targetLookup);
	if (building) {
		if (aStar.search(unit.tile, building->tile, unit.style.pathableTypes)) {
			std::list<Vec2i> path = aStar.path();
			ability.reset(new Garrison(unit, Lookup(*building), std::move(path)));
		}

	}
}
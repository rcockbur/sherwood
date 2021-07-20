#include "job.h"
#include "ability.h"
#include "entity_type.h"
#include "globals.h"
#include "pathfinding.h"

Job::Job(Unit& _unit) :
	unit(_unit),
	hasStarted(false)
{}

Job::~Job() {
	if (ability != nullptr) delete ability;
}

void Job::setAbility(Ability* _ability) {
	if (ability != nullptr) delete ability;
	ability = _ability;
}

void Job::destroyAbility() {
	if (ability != nullptr) delete ability;
	ability = nullptr;
}

ActivityStatus Job::start() {
	checkForAnotherAbility();
	if (ability == nullptr)
		return ActivityStatus::failure;
	hasStarted = true;
	return ability->start();
}

CompleteStatus Job::execute() {
	if (hasStarted == false)
		if(start() == ActivityStatus::failure)
			return CompleteStatus::complete;

	ActivityStatus abilityStatus = ability->execute();
	switch (abilityStatus) {
	case(ActivityStatus::success):
		destroyAbility();
		checkForAnotherAbility();
		if (ability == nullptr)
			return CompleteStatus::complete;
		else
			return CompleteStatus::incomplete;
	case(ActivityStatus::failure):
		return CompleteStatus::complete;
	default:
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
			Harvest* harvest = new Harvest(unit, depositLookup);
			setAbility(harvest);
		}
	}
	else {
		Building* house = breadthfirst.searchForHouse(unit.tile);
		if (house) {
			Lookup houseLookup = Lookup(*house);
			std::list<Vec2i> path = breadthfirst.path();
			ReturnResources* returnResources = new ReturnResources(unit, houseLookup, path);
			setAbility(returnResources);
		}
		//Building* home = em.lookupFixedEntity<Building*>(unit.homeLookup);
		/*if (home != nullptr) {
			ReturnResources* returnResources = new ReturnResources(unit, unit.homeLookup);
			setAbility(returnResources);
		}*/
	}
}

Mover::Mover(Unit& _unit, const Vec2i targetTile) :
	Job(_unit),
	targetTile(targetTile)
{}

void Mover::checkForAnotherAbility() {
	if (hasStarted == false) {
		hasStarted = true;
		Move* move = new Move(unit, targetTile);
		setAbility(move);
	}
}
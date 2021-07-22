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

Job::~Job() {
	//if (ability != nullptr) {
	//	delete ability;
	//}
}

//void Job::setAbility(std::unique_ptr<Ability>&& _ability) {
//	//if (ability != nullptr) {
//	//	delete ability;
//	//}
//	ability = std::move(_ability);
//}

//void Job::destroyAbility() {
//	//if (ability != nullptr) {
//	//	delete ability;
//	//}
//	//ability = nullptr;
//	ability.reset();
//}

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
			//destroyAbility();
			ability.reset();
			return CompleteStatus::complete;
		}
	}
	ActivityStatus abilityStatus = ability->execute();
	switch (abilityStatus) {
	case(ActivityStatus::inProgress):
		return CompleteStatus::incomplete;
	default:
		//destroyAbility();
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
				/*Harvest* harvest = new Harvest(unit, depositLookup, std::move(path));
				setAbility(harvest);*/
				ability.reset(new Harvest(unit, depositLookup, std::move(path)));
			}
		}
	}
	else {
		FixedEntity* targetHouse = newBreadthFirst.searchForFixedEntityType(unit.tile, house);
		if (targetHouse) {
			Lookup houseLookup = Lookup(*targetHouse);
			std::list<Vec2i> path = newBreadthFirst.path();
			/*ReturnResources* returnResources = new ReturnResources(unit, houseLookup, std::move(path));
			setAbility(returnResources);*/
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
			/*Move* move = new Move(unit, targetTile, std::move(path));
			setAbility(move);*/
			ability.reset(new Move(unit, targetTile, std::move(path)));
		}
		
	}
}
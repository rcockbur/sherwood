#include "job.h"
#include "ability.h"
#include "entity_type.h"
#include "globals.h"

Job::Job(Unit& _unit) :
	unit(_unit)
{}

Harvester::Harvester(Unit& _unit, const Lookup depositLookup) :
	Job(_unit),
	depositLookup(depositLookup),
	forcedHarvest(true)
{}

Status Harvester::addAbility() {
	if (forcedHarvest == true || unit.carryAmmount == 0) {
		Deposit* deposit = em.lookupFixedEntity<Deposit*>(depositLookup);
		if (deposit == nullptr) {
			return success;
		}
		else {
			forcedHarvest = false;
			std::cout << "issuing harvest ability\n";
			Harvest* harvest = new Harvest(unit, depositLookup);
			unit.setAbility(harvest);
			return inProgress;
		}
	}
	else {
		Building* home = em.lookupFixedEntity<Building*>(unit.homeLookup);
		if (home == nullptr) {
			return failure;
		}
		else {
			std::cout << "issuing return ability\n";
			ReturnResources* returnResources = new ReturnResources(unit, unit.homeLookup);
			unit.setAbility(returnResources);
			return inProgress;
		}
	}
}
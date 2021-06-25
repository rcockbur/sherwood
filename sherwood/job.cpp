#include "job.h"
#include "ability.h"
#include "entity_type.h"
#include "globals.h"
//#include "actions.h"

Job::Job(Unit& _unit) :
	unit(_unit)
{}

Harvester::Harvester(Unit& _unit, Deposit& deposit) :
	Job(_unit),
	depositID(deposit.id)
{}

bool Harvester::addAbility() {
	if (unit.carryAmmount < unit.type.carryCapacity) {
		auto it = em.depositMap.find(depositID);
		Deposit* deposit = (it == em.depositMap.end()) ? nullptr : it->second;
		if (deposit != nullptr) {
			if (astar.search(unit.tile, deposit->tile)) {
				std::list<Vec2i> path = astar.path(true);
				Harvest* harvest = new Harvest(unit, path, *deposit);
				unit.setAbility(harvest);
			}
			return false;
		}
		else {
			return true;
		}
	}
	else {
		if (unit.home == nullptr) {
			return true;
		}
		else {
			if (astar.search(unit.tile, unit.home->tile)) {
				std::list<Vec2i> path = astar.path(true);
				ReturnResources* returnResources = new ReturnResources(unit, path);
				unit.setAbility(returnResources);
			}
			return false;
		}
	}
}
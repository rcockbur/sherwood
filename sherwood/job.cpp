#include "job.h"
#include "ability.h"
//#include "actions.h"

Job::Job(Unit& _unit) :
	unit(_unit)
{}

Harvester::Harvester(Unit& _unit, Deposit& _deposit) :
	Job(_unit),
	deposit(_deposit)
{}

bool Harvester::addAbility() {
	if (unit.carryAmmount > 0) {
		if (astar.search(unit.tile, unit.home->tile)) {
			std::list<Vec2i> path = astar.path(true);
			ReturnResources* returnResources = new ReturnResources(unit, path);
			unit.setAbility(returnResources);
		}
		return false;
	}
	else {
		if (deposit.amount > 0) {
			//unitHarvestDeposit(&unit, &deposit);
			if (astar.search(unit.tile, deposit.tile)) {
				std::list<Vec2i> path = astar.path(true);
				Harvest* harvest = new Harvest(unit, path, deposit);
				unit.setAbility(harvest);
			}
			return false;
		}
		else {
			return true;
		}
		
	}
}
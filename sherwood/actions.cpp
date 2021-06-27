#include "actions.h"
#include "globals.h"
#include "pathfinding.h"
#include "job.h"

void unitMoveToTile(Unit& unit, Vec2i targetTile) {
	unit.destroyJobs();
	Move* move = new Move(unit, targetTile);
	if (shiftIsDown) {
		unit.addAbility(move);
	}
	else {
		unit.setAbility(move);
	}
}

void unitHarvestDeposit(Unit& unit, Deposit& deposit) {
	std::cout << "assigning harvester job\n";
	Harvester* harvester = new Harvester(unit, deposit);
	if (shiftIsDown) {
		unit.addJob(harvester);
	}
	else {
		unit.setJob(harvester);
	}
}

void unitReturnResources(Unit& unit) {
	
	ReturnResources* returnResources = new ReturnResources(unit, unit.homeLookup);
	unit.destroyJobs();
	if (shiftIsDown) {
		unit.addAbility(returnResources);
	}
	else {
		unit.setAbility(returnResources);
	}
}
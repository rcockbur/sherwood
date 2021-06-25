#include "actions.h"
#include "globals.h"
#include "pathfinding.h"
#include "job.h"

void unitMoveToTile(Unit* unit, Vec2i targetTile) {
	if (astar.search(unit->tile, targetTile)) {
		std::list<Vec2i> path = astar.path(false);
		Move* move = new Move(*unit, path);
		unit->setAbility(move);
	}
}

void unitHarvestDeposit(Unit& unit, Deposit& deposit) {
	Harvester* harvester = new Harvester(unit, deposit);
	unit.setJob(harvester);
}

void unitReturnResources(Unit* unit) {
	if (astar.search(unit->tile, unit->home->tile)) {
		std::list<Vec2i> path = astar.path(true);
		ReturnResources* returnResources = new ReturnResources(*unit, path);
		unit->setAbility(returnResources);
	}
}
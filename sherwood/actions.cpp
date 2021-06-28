#include "actions.h"
#include "globals.h"
#include "pathfinding.h"
#include "job.h"

void unitMoveToTile(Unit& unit, Vec2i targetTile) {
	if (map.isPathable(targetTile) == true) {
		Mover* mover = new Mover(unit, targetTile);
		if (shiftIsDown) {
			unit.addJob(mover);
		}
		else {
			ActivityStatus status = mover->start();
			if (status == ActivityStatus::success)
				unit.setJob(mover);
		}
	}
}

void unitHarvestDeposit(Unit& unit, Deposit& deposit) {
	Harvester* harvester = new Harvester(unit, deposit);
	if (shiftIsDown) {
		unit.addJob(harvester);
	}
	else {
		ActivityStatus status = harvester->start();
		if (status == ActivityStatus::success)
			unit.setJob(harvester);
	}
}

void unitReturnResources(Unit& unit) {}
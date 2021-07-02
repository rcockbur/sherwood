#include "actions.h"
#include "globals.h"
#include "pathfinding.h"
#include "job.h"
#include "utility.h"

void handleWorldClick(const Vec2f screenPos, const bool isLeftClick) {
	Vec2f worldPos = screenToWorld(screenPos);
	//std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
	Vec2i clickedTile = worldToTile(worldPos);
	//std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
	Entity* clickedEntity = em.getEntityAtWorldPos(worldPos);
	if (isLeftClick) {
		if (clickedEntity != nullptr)
			em.selectEntity(clickedEntity);
	}
	else {
		Unit* selectedUnit = dynamic_cast<Unit*>(selectedEntity);
		if (selectedUnit != nullptr) {
			Deposit* clickedDeposit = dynamic_cast<Deposit*>(clickedEntity);
			Building* clickedBuilding = dynamic_cast<Building*> (clickedEntity);
			if (clickedDeposit != nullptr)
				unitHarvestDeposit(*selectedUnit, *clickedDeposit);
			else if (clickedBuilding != nullptr) {
				if (*clickedBuilding == selectedUnit->homeLookup && selectedUnit->carryAmmount > 0)
					unitReturnResources(*selectedUnit);
			}
			else if (selectedEntity->tile != clickedTile) {
				unitMoveToTile(*selectedUnit, clickedTile);
			}
		}
	}
}

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
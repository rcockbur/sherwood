#include "actions.h"
#include "globals.h"
#include "pathfinding.h"
#include "job.h"
#include "utility.h"
#include "entity_style.h"

Entity* getEntityAtWorldPos(const Vec2f& worldPosition) {
	for (auto& entity : em.entities) {
		if (entity->bounds.contains(worldPosition)) {
			return entity;
		}
	}
	return nullptr;
}

void handleWorldClick(const Panel& panel, bool isLeftClick) {
	Vec2f worldPos = screenToWorld(mouseScreenPos);
	//std::cout << "WorldPosition:" << worldPosition.x << "," << worldPosition.y << "\n";
	Vec2i clickedTile = worldToTile(worldPos);
	std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
	Entity* clickedEntity = getEntityAtWorldPos(worldPos);
	if (isLeftClick) {
		if (placementBuildingType != nullptr) {
			if (mouseTile != Vec2i(-1, -1)) {
				new Building(*placementBuildingType, mouseTile);
				if (shiftIsDown == false) {
					placementBuildingType = nullptr;
				}
			}
		}

		else if (clickedEntity != nullptr)
			clickedEntity->select();
	}
	else {
		if (placementBuildingType) {
			placementBuildingType = nullptr;
		}
		else {
			Unit* selectedUnit = dynamic_cast<Unit*>(selectedEntity);
			if (selectedUnit != nullptr) {
				Deposit* clickedDeposit = dynamic_cast<Deposit*>(clickedEntity);
				Building* clickedBuilding = dynamic_cast<Building*> (clickedEntity);
				if (clickedDeposit != nullptr)
					unitHarvestDeposit(*selectedUnit, *clickedDeposit);
				else if (selectedEntity->tile != clickedTile) {
					unitMoveToTile(*selectedUnit, clickedTile);
				}
			}
		}
	}
}

void buildingButtonClicked(const Panel& panel, bool isLeftClick) {
	placementBuildingType = panel.getBuildingType();
}

void unitMoveToTile(Unit& unit, Vec2i targetTile) {
	if(unit.tileIsPathable(targetTile)) {
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
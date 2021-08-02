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

void handleWorldClick(bool left, bool down) {
	Vec2f worldPos = screenToWorld(mouseScreenPos);
	std::cout << "WorldPosition:" << worldPos.x << "," << worldPos.y << "\n";
	Vec2i clickedTile = worldToTile(worldPos);
	std::cout << "Tile:" << clickedTile.x << "," << clickedTile.y << "\n";
	Entity* clickedEntity = getEntityAtWorldPos(worldPos);
	if (left) {
		if (down) {
			//std::cout << "down\n";
			if (placementBuildingStyle) {
				if (mouseTile != Vec2i(-1, -1)) {
					new Building(*placementBuildingStyle, mouseTile);
					if (shiftIsDown == false) {
						placementBuildingStyle = nullptr;
					}
				}
			}
			else {
				selectionRectActive = true;
				selectionStartPos = worldPos;
			}
		}
		else {
			//std::cout << "up\n";
			if (selectionRectActive) {
				selectionRectActive = false;
				float rectLeft = std::min(selectionStartPos.x, mouseWorldPos.x);
				float rectRight = std::max(selectionStartPos.x, mouseWorldPos.x);
				float rectTop = std::min(selectionStartPos.y, mouseWorldPos.y);
				float rectBot = std::max(selectionStartPos.y, mouseWorldPos.y);
				Rect rect(rectLeft, rectTop, rectRight - rectLeft, rectBot - rectTop);
				selectedEntities.clear();
				if (rect.height > 0 && rect.width > 0) {
					for (auto entity : em.entities) {
						if (entity->bounds.intersects(rect)) {
							entity->select();
						}
					}
				}
				else {
					for (auto entity : em.entities) {
						if (entity->bounds.contains(mouseWorldPos)) {
							entity->select();
							break;
						}
					}
					
				}
				
			}
			
		}
		
	}
	else { //right
		if (down) {
			if (placementBuildingStyle) {
				placementBuildingStyle = nullptr;
			}
			else {
				for (auto entity : selectedEntities) {
					Unit* selectedUnit = dynamic_cast<Unit*>(entity);
					if (selectedUnit) {
						Deposit* clickedDeposit = dynamic_cast<Deposit*>(clickedEntity);
						Building* clickedBuilding = dynamic_cast<Building*> (clickedEntity);
						if (clickedDeposit != nullptr)
							unitHarvestDeposit(*selectedUnit, *clickedDeposit);
						else if (selectedUnit->tile != clickedTile) {
							unitMoveToTile(*selectedUnit, clickedTile);
						}
					}
				}
			}
		}
	}
}

void buildingButtonClicked(const Panel& panel, bool left, bool down) {
	if (left && down)
		placementBuildingStyle = panel.getBuildingStyle();
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
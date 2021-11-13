#include "actions.h"
#include "globals.h"
#include "pathfinding.h"
#include "job.h"
#include "utility.h"
#include "entity_style.h"

Entity* getEntityAtWorldPos(const Vec2f& worldPosition) {
	for (auto& it : em.entities) {
		if (it.second->bounds.contains(worldPosition)) {
			return it.second;
		}
	}
	return nullptr;
}

void handleWorldClick(bool left, bool down) {
	Vec2f worldPos = screenToWorld(mouseScreenPos);
	Vec2i clickedTile = worldToTile(worldPos);

	bool debugMouseClicks = false;
	if (debugMouseClicks) {
		std::string buttonName = left ? "LMB" : "RMB";
		std::string buttonState = down ? "Down" : "Up  ";
		std::cout << buttonName << " " << buttonState << " - ";
		std::cout << "Position: " << worldPos.x << "," << worldPos.y << " - ";
		std::cout << "Tile: " << clickedTile.x << "," << clickedTile.y << "\n";
	}
	
	Entity* clickedEntity = getEntityAtWorldPos(worldPos);
	if (left) {
		if (down) { //left down
			if (placementBuildingStyle) {
				if (mouseTile != Vec2i(-1, -1)) {
					new Fixed(*placementBuildingStyle, mouseTile);
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
		else { //left up
			if (selectionRectActive) {
				selectionRectActive = false;
				float rectLeft = std::min(selectionStartPos.x, mouseWorldPos.x);
				float rectRight = std::max(selectionStartPos.x, mouseWorldPos.x);
				float rectTop = std::min(selectionStartPos.y, mouseWorldPos.y);
				float rectBot = std::max(selectionStartPos.y, mouseWorldPos.y);
				Rect rect(rectLeft, rectTop, rectRight - rectLeft, rectBot - rectTop);
				selectedEntities.clear();
				if (rect.height > 0 && rect.width > 0) {
					for (auto it : em.entities) {
						if (it.second->bounds.intersects(rect)) {
							it.second->select();
						}
					}
				}
				else {
					for (auto it : em.entities) {
						if (it.second->bounds.contains(mouseWorldPos)) {
							it.second->select();
							break;
						}
					}
					
				}
			}
		}
	}
	else {
		if (down) { //right down
			if (placementBuildingStyle) {
				placementBuildingStyle = nullptr;
			}
			else { //right up
				for (auto entity : selectedEntities) {
					Unit* selectedUnit = dynamic_cast<Unit*>(entity);
					if (selectedUnit) {
						Fixed* clickedFixed = dynamic_cast<Fixed*>(clickedEntity);
						if (clickedFixed != nullptr) {
							if ((*clickedFixed).fixedStyle().resourceType != -1) {
								unitHarvestDeposit(*selectedUnit, *clickedFixed);
							}
						}
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

void unitHarvestDeposit(Unit& unit, Fixed& deposit) {
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
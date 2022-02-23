#pragma once
#include "types.h"

class Entity;
class Panel;

Entity* getEntityAtWorldPos(const Vec2f& worldPosition);
void handleWorldClick(bool left, bool down);
void entityButtonClicked(const Panel& panel, bool left, bool down);
void settingButtonClicked(const Panel& panel, bool left, bool down);
void unitMoveToTile(Entity& unit, Vec2i targetTile);
void unitHarvestDeposit(Entity& unit, Entity& deposit);
void unitGarrisonBuilding(Entity& unit, Entity& building);
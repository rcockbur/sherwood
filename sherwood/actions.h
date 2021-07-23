#pragma once
#include "types.h"

class Entity;
class Unit;
class Deposit;
class Panel;

Entity* getEntityAtWorldPos(const Vec2f& worldPosition);
void handleWorldClick(const Panel& panel, bool isRightClick);
void buildingButtonClicked(const Panel& panel, bool isLeftClick);
void unitMoveToTile(Unit& unit, Vec2i targetTile);
void unitHarvestDeposit(Unit& unit, Deposit& deposit);
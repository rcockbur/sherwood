#pragma once
#include "types.h"

class Entity;
class Unit;
class Fixed;
class Panel;

Entity* getEntityAtWorldPos(const Vec2f& worldPosition);
void handleWorldClick(bool left, bool down);
void buildingButtonClicked(const Panel& panel, bool left, bool down);
void unitMoveToTile(Unit& unit, Vec2i targetTile);
void unitHarvestDeposit(Unit& unit, Fixed& deposit);
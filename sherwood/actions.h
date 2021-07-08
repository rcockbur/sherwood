#pragma once
#include "types.h"

class Unit;
class Deposit;
class Panel;

void handleWorldClick(const Panel& panel, bool isRightClick);
void buildingButtonClicked(const Panel& panel, bool isLeftClick);
void unitMoveToTile(Unit& unit, Vec2i targetTile);
void unitHarvestDeposit(Unit& unit, Deposit& deposit);
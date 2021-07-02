#pragma once
#include "types.h"
#include "entity.h"
#include "ability.h"

void handleWorldClick(const Vec2f worldPosition, const bool isRightClick);
void unitMoveToTile(Unit& unit, Vec2i targetTile);
void unitHarvestDeposit(Unit& unit, Deposit& deposit);
void unitReturnResources(Unit& unit);
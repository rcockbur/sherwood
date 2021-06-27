#pragma once
#include "types.h"
//#include "globals.h"
#include "entity.h"
#include "ability.h"

void unitMoveToTile(Unit& unit, Vec2i targetTile);
void unitHarvestDeposit(Unit& unit, Deposit& deposit);
void unitReturnResources(Unit& unit);
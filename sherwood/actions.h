#pragma once
#include "types.h"
#include "entity.h"
#include "ability.h"
#include "panel.h"

void handleWorldClick(const Panel& panel, const bool isRightClick);
//void houseButtonClicked(const bool isRightClick);
//void millButtonClicked(const bool isRightClick);
void buildingButtonClicked(const Panel& panel, const bool isLeftClick);
void unitMoveToTile(Unit& unit, Vec2i targetTile);
void unitHarvestDeposit(Unit& unit, Deposit& deposit);
void unitReturnResources(Unit& unit);
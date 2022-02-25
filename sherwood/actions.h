#pragma once
#include "types.h"

class Entity;
class Panel;

void deselectNonPeople();
void deselectAll();
void unitMoveToTile(Entity& unit, Vec2i targetTile);
void unitHarvestDeposit(Entity& unit, Entity& deposit);
void unitGarrisonBuilding(Entity& unit, Entity& building);
void deleteEntities(std::set<Entity*>& entities);
void updateFPS(int fps);
void entityButtonClicked(const Panel& panel, bool left, bool down);
void settingButtonClicked(const Panel& panel, bool left, bool down);
void worldClicked(const Panel& panel, bool left, bool down);
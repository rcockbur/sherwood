#pragma once
#include "entity_manager.h"
#include "graphics.h"
#include "map.h"
#include "pathfinding.h"
#include <string>
#include "ui.h"

class UnitType;

extern bool showGrid;
extern bool showPathfinding;
extern bool hasPrinted;
extern bool shiftIsDown;
extern int tics;
extern int seconds;
extern int targetFPS;
extern float actualFPS;

extern sf::View mapView;
extern sf::RenderWindow renderWindow;

extern Map map;
extern Graphics graphics;
extern EntityManager em;
extern UI ui;
extern aStar astar;

extern Entity* selectedEntity;
extern BuildingType* placementBuildingType;
extern Vec2f mouseScreenPos;
extern Vec2f mouseWorldPos;
extern Vec2i mouseTile;
extern sf::Clock deltaClock;
extern sf::Clock gameClock;
extern sf::Time dt;

extern UnitType person;
extern DoodadType rock;
extern BuildingType house;
extern BuildingType mill;
extern DepositType berryBush;
extern DepositType tree;
extern DepositType goldMine;
extern DepositType stoneMine;

void initEntityTypes();
void initWindow();
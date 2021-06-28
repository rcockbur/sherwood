#pragma once
#include "entity_manager.h"
#include "graphics.h"
#include "map.h"
#include "input.h"
#include "pathfinding.h"
#include <string>

class UnitType;

extern bool showGrid;
extern bool showPathfinding;
extern bool hasPrinted;
extern bool shiftIsDown;
extern int tics;
extern int seconds;
extern int targetFPS;
extern float actualFPS;


extern Entity* selectedEntity;
extern sf::Clock deltaClock;
extern sf::Clock gameClock;
extern sf::Time dt;

extern Map map;
extern sf::View mapView;
extern sf::RenderWindow renderWindow;
extern const Vec2f GRID_SIZE;

extern Graphics graphics;
extern EntityManager em;
extern Input input;
extern aStar astar;


extern UnitType person;
extern DoodadType rock;
extern BuildingType house;
extern DepositType berryBush;
extern DepositType tree;
extern DepositType goldMine;
extern DepositType stoneMine;

void initEntityTypes();
void initWindow();
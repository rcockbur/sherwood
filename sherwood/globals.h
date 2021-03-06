#pragma once
#include "entity_manager.h"
#include "graphics.h"
#include "map.h"
#include "pathfinding.h"
#include <string>
#include "ui.h"
#include <set>

class UnitStyle;

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
extern AStar aStar;
extern BreadthFirst breadthFirst;

//extern Entity* selectedEntity;
extern std::set<Entity*> selectedEntities;
extern BuildingStyle* placementBuildingStyle;
extern Vec2f mouseScreenPos;
extern Vec2f mouseWorldPos;
extern Vec2i mouseTile;
extern Vec2f selectionStartPos;
//extern Vec2f selectionEndPos;
extern bool selectionRectActive;

extern sf::Clock deltaClock;
extern sf::Clock gameClock;
extern sf::Time dt;

extern UnitStyle person;
extern DoodadStyle rock;
extern BuildingStyle house;
extern BuildingStyle mill;
extern DepositStyle berryBush;
extern DepositStyle fish;
extern DepositStyle tree;
extern DepositStyle goldMine;
extern DepositStyle stoneMine;

void initEntityStyles();
void initWindow();
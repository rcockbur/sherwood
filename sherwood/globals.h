#pragma once
#include "entity_manager.h"
#include "graphics.h"
#include "map.h"
#include "pathfinding.h"
#include <string>
#include "ui.h"
#include <set>

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

extern std::set<Entity*> selectedEntities;
extern const EntityStyle* placementEntityStyle;
extern Vec2f mouseScreenPos;
extern Vec2f mouseWorldPos;
extern Vec2i mouseTile;
extern Vec2f selectionStartPos;
extern bool selectionRectActive;

extern sf::Clock deltaClock;
extern sf::Clock gameClock;
extern sf::Time dt;

extern const EntityStyle PERSON;
extern const EntityStyle ROCK;
extern const EntityStyle HOUSE;
extern const EntityStyle MILL;
extern const EntityStyle BERRY_BUSH;
extern const EntityStyle FISH;
extern const EntityStyle TREE;
extern const EntityStyle GOLD_MINE;
extern const EntityStyle STONE_MINE;

void initEntityStyles();
void initWindow();
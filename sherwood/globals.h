#pragma once
#include "entity_manager.h"
#include "graphics_manager.h"
#include "map.h"
#include "window_manager.h"
#include "input_manager.h"
#include "pathfinding.h"

extern bool showGrid;
extern bool hasPrinted;
extern Entity* selectedEntity;
extern uint tic;
extern sf::Clock deltaClock;
extern sf::Time dt;

extern Map map;
extern WindowManager wm;
extern GraphicsManager gm;
extern EntityManager em;
extern InputManager im;
extern aStar astar;

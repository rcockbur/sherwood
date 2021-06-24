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
extern int tic;
extern int targetFPS;
extern float actualFPS;
extern Entity* selectedEntity;
extern sf::Clock deltaClock;
extern sf::Time dt;

extern const float LINE_WIDTH_HALF;
extern const float LINE_WIDTH;
extern const float TILE_SIZE;
extern const float ENTITY_SIZE;
extern const float PATH_DEBUG_SIZE;
extern const Vec2u WINDOW_SIZE;
extern const float WINDOW_PADDING_TOP;
extern const float WINDOW_PADDING_LEFT;
extern const float WINDOW_PADDING_BOT;
extern const float TOP_PANEL_HEIGHT;
extern const float VIEWPORT_WIDTH;
extern const Vec2f VIEWPORT_SIZE;
extern const Vec2f VIEWPORT_OFFSET;
extern const sf::Rect<float> VIEWPORT_RECT;
extern const Vec2f RIGHT_PANEL_OFFSET;

extern Map map;
extern sf::View mapView;
extern sf::RenderWindow renderWindow;
extern const Vec2f GRID_SIZE;

extern Graphics graphics;
extern EntityManager em;
extern Input input;
extern aStar astar;

constexpr int NUM_RESOURCES = 2;
extern const std::string resourceNames[NUM_RESOURCES];

extern UnitType person;
extern DoodadType rock;
extern BuildingType house;
extern DepositType berryBush;
extern DepositType tree;

void initEntityTypes();
void initWindow();
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

extern const float LINE_WIDTH_HALF;
extern const float LINE_WIDTH;
extern const Vec2f TILE_SIZE;
extern const Vec2f ENTITY_SIZE;
extern const Vec2f PATH_DEBUG_SIZE;
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
extern WindowManager wm;
extern GraphicsManager gm;
extern EntityManager em;
extern InputManager im;
extern aStar astar;
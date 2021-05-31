#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"
#include "pathfinding.h"

bool showGrid = true;
bool hasPrinted = false;
Entity* selectedEntity(nullptr);
uint tic(0);
sf::Clock deltaClock;
sf::Time dt = deltaClock.restart();

const float LINE_WIDTH_HALF(0.5);
const float LINE_WIDTH(LINE_WIDTH_HALF * 2);
const Vec2f TILE_SIZE(24, 24);
const Vec2f ENTITY_SIZE(16, 16);
const Vec2f PATH_DEBUG_SIZE(8, 8);
const Vec2u WINDOW_SIZE(800, 450);
const float WINDOW_PADDING_TOP(5);
const float WINDOW_PADDING_LEFT(5);
const float WINDOW_PADDING_BOT(10);
const float TOP_PANEL_HEIGHT(20);
const float VIEWPORT_WIDTH(580);
const Vec2f VIEWPORT_SIZE(VIEWPORT_WIDTH, WINDOW_SIZE.y - WINDOW_PADDING_TOP - WINDOW_PADDING_BOT - TOP_PANEL_HEIGHT);
const Vec2f VIEWPORT_OFFSET(WINDOW_PADDING_LEFT, WINDOW_PADDING_TOP + TOP_PANEL_HEIGHT);
const sf::Rect<float> VIEWPORT_RECT(VIEWPORT_OFFSET, VIEWPORT_SIZE);
const Vec2f RIGHT_PANEL_OFFSET(VIEWPORT_OFFSET.x + VIEWPORT_SIZE.x + 3, VIEWPORT_OFFSET.y);

Map map("data/map.txt");
WindowManager wm("Sherwood", 60);
GraphicsManager gm;
EntityManager em;
InputManager im;
aStar astar;

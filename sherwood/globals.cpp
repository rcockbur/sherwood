#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "colors.h"

bool showGrid = true;
bool hasPrinted = false;
Entity* selectedEntity(nullptr);
uint tic(0);
sf::Clock deltaClock;
sf::Time dt = deltaClock.restart();

Map map("data/map.txt");
WindowManager wm("Sherwood", 30);
GraphicsManager gm;
EntityManager em;
InputManager im;

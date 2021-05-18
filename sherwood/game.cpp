#include "game.h"

bool showGrid = true;
Entity* selectedEntity(nullptr);

Map map("data/map.txt");
WindowManager wm("Sherwood", 30);
GraphicsManager gm;
EntityManager em;
InputManager im;
#pragma once
#include "types.h"

class Map;
class Window;
class EntityManager;

void handleInput();
void handleKeysDown();
void handleKeyPress(sf::Keyboard::Key);
void updateFPS(int fps);

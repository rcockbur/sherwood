#pragma once
#include "map.h"
#include "entity_manager.h"

struct Colors {
	sf::Color blue = sf::Color::Blue;
	sf::Color black = sf::Color::Black;
	sf::Color green = sf::Color::Green;
	sf::Color red = sf::Color::Red;
	sf::Color white = sf::Color::White;
	sf::Color yellow = sf::Color::Yellow;
	sf::Color grey = sf::Color(100, 100, 100);
	sf::Color transparent = sf::Color(0, 0, 0, 0);
};

void initGraphics();
void drawAll();
void drawTerrain();
void drawGrid();
void drawEntities();
void drawViewportOutline();
void drawText();
void updateFPS(uint);

#include "globals.h"
#include "map.h"
#include "entity_manager.h"

sf::RenderWindow window(sf::VideoMode(400, 400), "Sherwood");

Map map({ 10,10 }, { 15., 15. }, 2., sf::Color::White);

EntityManager em = EntityManager();

Vec2f cameraPos{ 0,0 };
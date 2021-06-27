#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Entity;

typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2u Vec2u;
typedef sf::Color Color;
typedef sf::Rect<float> Rect;

//enum RT { food }; 
enum ResourceType { food, wood };
enum Status { success, failure, inProgress };

std::ostream& operator<< (std::ostream& out, const Vec2i& vec);
std::ostream& operator<< (std::ostream& out, const Vec2f& vec);
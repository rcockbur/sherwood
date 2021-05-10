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
typedef unsigned int uint;

enum class ET{ DEER };
constexpr uint ENTITY_TYPES = 1;
enum class AT{ MOVE };

extern const float lineWidthHalf;
extern const float lineWidth;
extern const Vec2f tileSize;
extern const Vec2f entitySize;
extern const Vec2u windowSize;
extern const float windowPaddingTop;
extern const float windowPaddingLeft;
extern const float windowPaddingBot;
extern const float topPanelHeight;
extern const float viewportWidth;
extern const Vec2f viewportSize;
extern const Vec2f viewportOffset;
extern const sf::Rect<float> viewportRect;
extern const Vec2f rightPannelPosition;
extern Entity* selectedEntity;
//extern const Vec2f gridSize;


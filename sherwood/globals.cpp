#include "globals.h"

const float lineWidthHalf = 0.5;
const float lineWidth = lineWidthHalf * 2;
const Vec2f tileSize{ 24, 24 };
const Vec2f entitySize{ tileSize.x - lineWidth, tileSize.y - lineWidth };
const Vec2i tileCount{ 30, 20 };
const Vec2u windowSize{ 800, 450 };
const float windowPaddingTop{ 5 };
const float windowPaddingLeft{ 5 };
const float windowPaddingBot{ 10 };
const float topPanelHeight{ 20 };
const float viewportWidth{ 580 };
const Vec2f viewportSize{ viewportWidth, windowSize.y - windowPaddingTop - windowPaddingBot - topPanelHeight };
const Vec2f viewportOffset{ Vec2f(windowPaddingLeft, windowPaddingTop + topPanelHeight) };
const sf::Rect<float> viewportRect(viewportOffset, viewportSize);
const Vec2f rightPannelPosition(viewportOffset.x + viewportSize.x + 3, viewportOffset.y);
Entity* selectedEntity(nullptr);

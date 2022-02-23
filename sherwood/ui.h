#pragma once
#include "panel.h"

class UI {
public:
	Panel hud;

	Panel topPanel;
	Panel targetFpsPanel;
	Panel actualFpsPanel;
	Panel unitCountPanel;
	Panel houseCountPanel;
	Panel timePanel;

	Panel viewportPanel;
	Panel rightPanel;
	Panel selectionPanel;
	Panel buttonGridPanel;
	Panel houseButton;
	Panel millButton;
	Panel personButton;
	sf::Text text;
	sf::Font font;
	UI();
};
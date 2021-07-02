#pragma once
#include "constants.h"
#include "types.h"
#include <vector>
#include "panel.h"

class UI {
public:
	Panel hud;

	Panel topPanel;
	Panel targetFpsPanel;
	Panel actualFpsPanel;
	Panel unitCountPanel;
	Panel timePanel;

	Panel viewportPanel;
	Panel rightPanel;
	Panel selectionPanel;
	Panel buttonGridPanel;
	Panel houseButton;
	Panel millButton;
	sf::Text text;
	sf::Font font;
	UI();
};
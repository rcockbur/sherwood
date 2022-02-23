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

	Panel buttonRow1;
	Panel buttonRow2;
	Panel buttonRow3;
	Panel buttonRow4;
	Panel buttonRow5;
	Panel buttonRow6;
	Panel buttonRow7;
	Panel buttonRow8;
	Panel buttonRow9;

	Panel houseButton;
	Panel millButton;

	Panel berryButton;
	Panel fishButton;
	Panel woodButton;
	Panel goldButton;
	Panel stoneButton;

	Panel personButton;

	Panel showGridButton;
	Panel showPathfindingButton;
	
	sf::Text text;
	sf::Font font;
	UI();
};
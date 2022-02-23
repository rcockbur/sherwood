#include "ui.h"
#include "globals.h"
#include "color.h"
#include "input.h"
#include "actions.h"


UI::UI()
{
	if (!font.loadFromFile("resources/sansation.ttf"))
		throw std::logic_error("font cannot be found");

	hud.setName("hud");
	hud.setSize(Vec2f(1200, 700));
	hud.setPadding(Padding(5, 3, 5, 3));

	topPanel.setName("topPanel");
	topPanel.setParent(hud);
	topPanel.setPadding(Padding(5, 1, 0, 0));
	topPanel.setSize(Vec2f(-1, 20));

	targetFpsPanel.setName("targetFpsPanel");
	targetFpsPanel.setParent(topPanel);
	targetFpsPanel.setSize((Vec2f(100, -1)));

	actualFpsPanel.setName("actualFpsPanel");
	actualFpsPanel.setParent(topPanel);
	actualFpsPanel.moveRightOfPanel(targetFpsPanel);
	actualFpsPanel.setSize((Vec2f(100, -1)));

	timePanel.setName("timePanel");
	timePanel.setParent(topPanel);
	timePanel.moveRightOfPanel(actualFpsPanel);
	timePanel.setSize((Vec2f(100, -1)));

	unitCountPanel.setName("unitCountPanel");
	unitCountPanel.setParent(topPanel);
	unitCountPanel.moveRightOfPanel(timePanel);
	unitCountPanel.setSize((Vec2f(100, -1)));

	houseCountPanel.setName("houseCountPanel");
	houseCountPanel.setParent(topPanel);
	houseCountPanel.moveRightOfPanel(unitCountPanel);
	houseCountPanel.setSize((Vec2f(100, -1)));

	viewportPanel.setName("viewportPanel");
	viewportPanel.setParent(hud);
	viewportPanel.moveBelowPanel(topPanel);
	viewportPanel.setSize(Vec2f(900, 650));
	viewportPanel.setBorderColor(colors.blue);
	//viewportPanel.setCallback(handleWorldClick);

	rightPanel.setName("rightPanel");
	rightPanel.setParent(hud);
	
	rightPanel.moveRightOfPanel(viewportPanel);
	rightPanel.moveBelowPanel(topPanel);
	rightPanel.setSize(Vec2f(-1, viewportPanel.size.y));
	//rightPanel.setBorderColor(colors.red);

	selectionPanel.setName("selectionPanel");
	selectionPanel.setParent(rightPanel);
	selectionPanel.setPadding(Padding(5, 3, 0, 0));
	selectionPanel.setSize((Vec2f(-1, 200)));

	buttonGridPanel.setName("buttonGridPanel");
	buttonGridPanel.setParent(rightPanel);
	buttonGridPanel.setPadding(Padding(0, 0, 0, 0));
	buttonGridPanel.moveBelowPanel(selectionPanel);
	buttonGridPanel.setSize(Vec2f(-1, -1));
	//buttonGridPanel.setBorderColor(colors.red);
	
	Vec2f BUTTON_SIZE(50, 50);

	buttonRow1.setName("buttonRow1");
	buttonRow1.setParent(buttonGridPanel);
	buttonRow1.setSize(Vec2f(-1, BUTTON_SIZE.y));
	
	buttonRow2.setName("buttonRow2");
	buttonRow2.setParent(buttonGridPanel);
	buttonRow2.moveBelowPanel(buttonRow1);
	buttonRow2.setSize(Vec2f(-1, BUTTON_SIZE.y));

	buttonRow3.setName("buttonRow3");
	buttonRow3.setParent(buttonGridPanel);
	buttonRow3.moveBelowPanel(buttonRow2);
	buttonRow3.setSize(Vec2f(-1, BUTTON_SIZE.y));

	buttonRow4.setName("buttonRow4");
	buttonRow4.setParent(buttonGridPanel);
	buttonRow4.moveBelowPanel(buttonRow3);
	buttonRow4.setSize(Vec2f(-1, BUTTON_SIZE.y));

	buttonRow5.setName("buttonRow5");
	buttonRow5.setParent(buttonGridPanel);
	buttonRow5.moveBelowPanel(buttonRow4);
	buttonRow5.setSize(Vec2f(-1, BUTTON_SIZE.y));

	buttonRow6.setName("buttonRow6");
	buttonRow6.setParent(buttonGridPanel);
	buttonRow6.moveBelowPanel(buttonRow5);
	buttonRow6.setSize(Vec2f(-1, BUTTON_SIZE.y));

	buttonRow7.setName("buttonRow7");
	buttonRow7.setParent(buttonGridPanel);
	buttonRow7.moveBelowPanel(buttonRow6);
	buttonRow7.setSize(Vec2f(-1, BUTTON_SIZE.y));

	buttonRow8.setName("buttonRow8");
	buttonRow8.setParent(buttonGridPanel);
	buttonRow8.moveBelowPanel(buttonRow7);
	buttonRow8.setSize(Vec2f(-1, BUTTON_SIZE.y));

	buttonRow9.setName("buttonRow9");
	buttonRow9.setParent(buttonGridPanel);
	buttonRow9.moveBelowPanel(buttonRow8);
	buttonRow9.setSize(Vec2f(-1, BUTTON_SIZE.y));

	houseButton.setName("houseButton");
	houseButton.setParent(buttonRow1);
	houseButton.setString("House");
	houseButton.setSize(BUTTON_SIZE);
	houseButton.setBorderColor(colors.white);
	houseButton.setPadding(Padding(3, 3, 3, 3));
	houseButton.setCallback(entityButtonClicked);
	houseButton.setentityStyle(&HOUSE);

	millButton.setName("millButton");
	millButton.setParent(buttonRow1);
	millButton.setString("Mill");
	millButton.moveRightOfPanel(houseButton);
	millButton.setSize(BUTTON_SIZE);
	millButton.setBorderColor(colors.white);
	millButton.setPadding(Padding(3, 3, 3, 3));
	millButton.setCallback(entityButtonClicked);
	millButton.setentityStyle(&MILL);

	berryButton.setName("berryButton");
	berryButton.setParent(buttonRow2);
	berryButton.setString("Berries");
	berryButton.setSize(BUTTON_SIZE);
	berryButton.setBorderColor(colors.white);
	berryButton.setPadding(Padding(3, 3, 3, 3));
	berryButton.setCallback(entityButtonClicked);
	berryButton.setentityStyle(&BERRY_BUSH);

	fishButton.setName("fishButton");
	fishButton.setParent(buttonRow2);
	fishButton.setString("Fish");
	fishButton.moveRightOfPanel(berryButton);
	fishButton.setSize(BUTTON_SIZE);
	fishButton.setBorderColor(colors.white);
	fishButton.setPadding(Padding(3, 3, 3, 3));
	fishButton.setCallback(entityButtonClicked);
	fishButton.setentityStyle(&FISH);

	woodButton.setName("woodButton");
	woodButton.setParent(buttonRow2);
	woodButton.setString("Tree");
	woodButton.moveRightOfPanel(fishButton);
	woodButton.setSize(BUTTON_SIZE);
	woodButton.setBorderColor(colors.white);
	woodButton.setPadding(Padding(3, 3, 3, 3));
	woodButton.setCallback(entityButtonClicked);
	woodButton.setentityStyle(&TREE);

	goldButton.setName("goldButton");
	goldButton.setParent(buttonRow2);
	goldButton.setString("Gold");
	goldButton.moveRightOfPanel(woodButton);
	goldButton.setSize(BUTTON_SIZE);
	goldButton.setBorderColor(colors.white);
	goldButton.setPadding(Padding(3, 3, 3, 3));
	goldButton.setCallback(entityButtonClicked);
	goldButton.setentityStyle(&GOLD_MINE);

	stoneButton.setName("stoneButton");
	stoneButton.setParent(buttonRow2);
	stoneButton.setString("Stone");
	stoneButton.moveRightOfPanel(goldButton);
	stoneButton.setSize(BUTTON_SIZE);
	stoneButton.setBorderColor(colors.white);
	stoneButton.setPadding(Padding(3, 3, 3, 3));
	stoneButton.setCallback(entityButtonClicked);
	stoneButton.setentityStyle(&STONE_MINE);

	personButton.setName("personButton");
	personButton.setParent(buttonRow3);
	personButton.setString("Person");
	personButton.setSize(BUTTON_SIZE);
	personButton.setBorderColor(colors.white);
	personButton.setPadding(Padding(3, 3, 3, 3));
	personButton.setCallback(entityButtonClicked);
	personButton.setentityStyle(&PERSON);

	showGridButton.setName("showGridButton");
	showGridButton.setParent(buttonRow9);
	showGridButton.setString("Show\nGrid");
	showGridButton.setSize(BUTTON_SIZE);
	showGridButton.setBorderColor(colors.white);
	showGridButton.setPadding(Padding(3, 3, 3, 3));
	showGridButton.setCallback(settingButtonClicked);
	showGridButton.setSetting(&showGrid);

	showPathfindingButton.setName("showPathfindingButton");
	showPathfindingButton.setParent(buttonRow9);
	showPathfindingButton.setString("Show\nPath\nFinding");
	showPathfindingButton.moveRightOfPanel(showGridButton);
	showPathfindingButton.setSize(BUTTON_SIZE);
	showPathfindingButton.setBorderColor(colors.white);
	showPathfindingButton.setPadding(Padding(3, 3, 3, 3));
	showPathfindingButton.setCallback(settingButtonClicked);
	showPathfindingButton.setSetting(&showPathfinding);
}


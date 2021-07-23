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

	viewportPanel.setName("viewportPanel");
	viewportPanel.setParent(hud);
	viewportPanel.moveBelowPanel(topPanel);
	viewportPanel.setSize(Vec2f(900, 660));
	viewportPanel.setBorderColor(colors.blue);
	viewportPanel.setCallback(handleWorldClick);

	rightPanel.setName("rightPanel");
	rightPanel.setParent(hud);
	
	rightPanel.moveRightOfPanel(viewportPanel);
	rightPanel.moveBelowPanel(topPanel);
	rightPanel.setSize(Vec2f(-1, viewportPanel.size.y));

	selectionPanel.setName("selectionPanel");
	selectionPanel.setParent(rightPanel);
	selectionPanel.setPadding(Padding(5, 3, 0, 0));
	selectionPanel.setSize((Vec2f(-1, 200)));

	buttonGridPanel.setName("buttonGridPanel");
	buttonGridPanel.setParent(rightPanel);
	buttonGridPanel.setPadding(Padding(0, 0, 0, 0));
	buttonGridPanel.moveBelowPanel(selectionPanel);
	buttonGridPanel.setSize(Vec2f(-1, -1));

	houseButton.setName("houseButton");
	houseButton.setParent(buttonGridPanel);
	houseButton.setString("House");
	houseButton.setSize(Vec2f(70, 50));
	houseButton.setBorderColor(colors.white);
	houseButton.setPadding(Padding(3, 3, 3, 3));
	houseButton.setCallback(buildingButtonClicked);
	houseButton.setBuildingType(&house);

	millButton.setName("millButton");
	millButton.setParent(buttonGridPanel);
	millButton.setString("Mill");
	millButton.moveRightOfPanel(houseButton);
	millButton.setSize(Vec2f(70, 50));
	millButton.setBorderColor(colors.white);
	millButton.setPadding(Padding(3, 3, 3, 3));
	millButton.setCallback(buildingButtonClicked);
	millButton.setBuildingType(&mill);
}


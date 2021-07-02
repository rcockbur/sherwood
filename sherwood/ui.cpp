#include "ui.h"
#include "globals.h"
#include "color.h"

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
	topPanel.setBorderColor(colors.red);
	//topPanel.border.setOutlineColor(colors.red);

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

	rightPanel.setName("rightPanel");
	rightPanel.setParent(hud);
	rightPanel.setPadding(Padding(5, 1, 0, 0));
	rightPanel.moveRightOfPanel(viewportPanel);
	rightPanel.moveBelowPanel(topPanel);
	rightPanel.setSize(Vec2f(-1, viewportPanel.size.y));
	rightPanel.setBorderColor(colors.yellow);

	selectionPanel.setName("selectionPanel");
	selectionPanel.setParent(rightPanel);
	selectionPanel.setSize((Vec2f(-1, -1)));
}


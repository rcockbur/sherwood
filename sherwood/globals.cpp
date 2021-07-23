#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"
#include "pathfinding.h"
#include "entity_style.h"
#include "types.h"


bool showGrid = true;
bool showPathfinding = false;
bool hasPrinted = false;
bool shiftIsDown = false;
int targetFPS = 30;
int tics = 0;
int seconds = 0;
float actualFPS = (float)targetFPS;
Entity* selectedEntity(nullptr);
BuildingStyle* placementBuildingType(nullptr);
Vec2f mouseScreenPos(0, 0);
Vec2f mouseWorldPos(-1, -1);
Vec2i mouseTile(-1, -1);

sf::Clock deltaClock;
sf::Clock gameClock;
sf::Time dt = deltaClock.restart();

const Colors colors;
Map map("data/map.txt");
UI ui;
sf::View mapView(sf::FloatRect(Vec2f(), ui.viewportPanel.getSize()));
//sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Sherwood", sf::Style::Fullscreen);
sf::RenderWindow renderWindow(sf::VideoMode((int)ui.hud.getSize().x, (int)ui.hud.getSize().y), "Sherwood");
Graphics graphics;
EntityManager em;
AStar aStar;
BreadthFirst breadthFirst;

UnitStyle person = UnitStyle("Person");
DoodadStyle rock = DoodadStyle("Rock");
BuildingStyle house = BuildingStyle("House");
BuildingStyle mill = BuildingStyle("Mill");
DepositStyle berryBush = DepositStyle("Berry Bush");
DepositStyle fish = DepositStyle("Fish");
DepositStyle tree = DepositStyle("Tree");
DepositStyle goldMine = DepositStyle("Gold Mine");
DepositStyle stoneMine = DepositStyle("Stone Mine");

RectangleShape FixedStyle::shape = RectangleShape();
RectangleShape FixedStyle::outlineShape = RectangleShape();
CircleShape UnitStyle::shape = CircleShape();
CircleShape UnitStyle::outlineShape = CircleShape();

void initEntityTypes() {
	person.color = colors.lightBlue;
	person.movePeriod = 1;
	person.moveDistance = 4.0f;
	person.carryCapacity = 10;
	person.gatherPeriod = 8;
	person.size = 12;
	person.pathableTypes.insert(1);

	rock.color = colors.darkGrey;
	rock.size = 12;
	rock.pathableTypes.insert(1);

	house.color = colors.black;
	house.resources[food] = 50;
	house.resources[wood] = 100;
	house.size = 16;
	house.pathableTypes.insert(1);

	mill.color = colors.orange;
	mill.size = 16;
	mill.pathableTypes.insert(1);

	berryBush.color = colors.red;
	berryBush.resourceType = food;
	berryBush.amount = 100;
	berryBush.size = 14;
	berryBush.pathableTypes.insert(1);

	fish.color = colors.blue;
	fish.resourceType = food;
	fish.amount = 100;
	fish.size = 10;
	fish.pathableTypes.insert(0);

	tree.color = colors.brown;
	tree.resourceType = wood;
	tree.amount = 100;
	tree.size = 12;
	tree.pathableTypes.insert(1);

	goldMine.color = colors.yellow;
	goldMine.resourceType = gold;
	goldMine.amount = 1000;
	goldMine.size = 12;
	goldMine.pathableTypes.insert(1);

	stoneMine.color = colors.darkGrey;
	stoneMine.resourceType = stone;
	stoneMine.amount = 1000;
	stoneMine.size = 12;
	stoneMine.pathableTypes.insert(1);

	FixedStyle::outlineShape.setFillColor(colors.transparent);
	FixedStyle::outlineShape.setOutlineColor(colors.lightYellow);
	FixedStyle::outlineShape.setOutlineThickness(-OUTLINE_WIDTH);

	UnitStyle::outlineShape.setFillColor(colors.transparent);
	UnitStyle::outlineShape.setOutlineColor(colors.lightYellow);
	UnitStyle::outlineShape.setOutlineThickness(-OUTLINE_WIDTH);
}

void initWindow() {
	renderWindow.setPosition(Vec2i(0, 0));
	renderWindow.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(DivideVec2<float>(ui.viewportPanel.getPosition(), ui.hud.getSize()));
	Vec2f viewportSizeRatio(DivideVec2<float>(ui.viewportPanel.getSize(), ui.hud.getSize()));
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	mapView.move(Vec2f(-10, -10));
}
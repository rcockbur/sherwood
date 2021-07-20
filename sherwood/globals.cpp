#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"
#include "pathfinding.h"
#include "entity_type.h"
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
BuildingType* placementBuildingType(nullptr);
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
aStar astar;
NewAStar newAstar;
breadthFirst breadthfirst;

UnitType person = UnitType("Person");
DoodadType rock = DoodadType("Rock");
BuildingType house = BuildingType("House");
BuildingType mill = BuildingType("Mill");
DepositType berryBush = DepositType("Berry Bush");
DepositType fish = DepositType("Fish");
DepositType tree = DepositType("Tree");
DepositType goldMine = DepositType("Gold Mine");
DepositType stoneMine = DepositType("Stone Mine");

RectangleShape FixedEntityType::shape = RectangleShape();
RectangleShape FixedEntityType::outlineShape = RectangleShape();
CircleShape UnitType::shape = CircleShape();
CircleShape UnitType::outlineShape = CircleShape();

void initEntityTypes() {
	person.color = colors.lightBlue;
	person.movePeriod = 1;
	person.moveDistance = 4.0f;
	person.carryCapacity = 10;
	person.gatherPeriod = 8;
	person.size = 12;

	rock.color = colors.darkGrey;
	rock.size = 12;

	house.color = colors.black;
	house.resources[food] = 50;
	house.resources[wood] = 100;
	house.size = 16;

	mill.color = colors.orange;
	mill.size = 16;

	berryBush.color = colors.red;
	berryBush.resourceType = food;
	berryBush.amount = 100;
	berryBush.size = 14;

	fish.color = colors.blue;
	fish.resourceType = food;
	fish.amount = 100;
	fish.size = 10;

	tree.color = colors.brown;
	tree.resourceType = wood;
	tree.amount = 100;
	tree.size = 12;

	goldMine.color = colors.yellow;
	goldMine.resourceType = gold;
	goldMine.amount = 1000;
	goldMine.size = 12;

	stoneMine.color = colors.darkGrey;
	stoneMine.resourceType = stone;
	stoneMine.amount = 1000;
	stoneMine.size = 12;

	FixedEntityType::outlineShape.setFillColor(colors.transparent);
	FixedEntityType::outlineShape.setOutlineColor(colors.lightYellow);
	FixedEntityType::outlineShape.setOutlineThickness(-OUTLINE_WIDTH);

	UnitType::outlineShape.setFillColor(colors.transparent);
	UnitType::outlineShape.setOutlineColor(colors.lightYellow);
	UnitType::outlineShape.setOutlineThickness(-OUTLINE_WIDTH);
}

void initWindow() {
	renderWindow.setPosition(Vec2i(0, 0));
	renderWindow.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(DivideVec2<float>(ui.viewportPanel.getPosition(), ui.hud.getSize()));
	Vec2f viewportSizeRatio(DivideVec2<float>(ui.viewportPanel.getSize(), ui.hud.getSize()));
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	mapView.move(Vec2f(-10, -10));
}
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
//Entity* selectedEntity(nullptr);
std::set<Entity*> selectedEntities;
const BuildingStyle* placementBuildingStyle(nullptr);
Vec2f mouseScreenPos(0, 0);
Vec2f mouseWorldPos(-1, -1);
Vec2i mouseTile(-1, -1);
Vec2f selectionStartPos = Vec2f();
bool selectionRectActive = false;

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

const UnitStyle PERSON = UnitStyle("Person");
const DoodadStyle ROCK = DoodadStyle("Rock");
const BuildingStyle HOUSE = BuildingStyle("House");
const BuildingStyle MILL = BuildingStyle("Mill");
const DepositStyle BERRY_BUSH = DepositStyle("Berry Bush");
const DepositStyle FISH = DepositStyle("Fish");
const DepositStyle TREE = DepositStyle("Tree");
const DepositStyle GOLD_MINE = DepositStyle("Gold Mine");
const DepositStyle STONE_MINE = DepositStyle("Stone Mine");

RectangleShape FixedStyle::shape = RectangleShape();
RectangleShape FixedStyle::outlineShape = RectangleShape();
CircleShape UnitStyle::shape = CircleShape();
CircleShape UnitStyle::outlineShape = CircleShape();

void initEntityStyles() {
	const_cast<UnitStyle&>(PERSON).color = colors.lightBlue;
	const_cast<UnitStyle&>(PERSON).movePeriod = 1;
	const_cast<UnitStyle&>(PERSON).moveDistance = 4.0f;
	const_cast<UnitStyle&>(PERSON).carryCapacity = 10;
	const_cast<UnitStyle&>(PERSON).gatherPeriod = 2;
	const_cast<UnitStyle&>(PERSON).size = 12;
	const_cast<UnitStyle&>(PERSON).pathableTypes.insert(1);

	const_cast<DoodadStyle&>(ROCK).color = colors.darkGrey;
	const_cast<DoodadStyle&>(ROCK).size = 12;
	const_cast<DoodadStyle&>(ROCK).pathableTypes.insert(1);

	const_cast<BuildingStyle&>(HOUSE).color = colors.black;
	const_cast<BuildingStyle&>(HOUSE).resources[food] = 50;
	const_cast<BuildingStyle&>(HOUSE).resources[wood] = 100;
	const_cast<BuildingStyle&>(HOUSE).size = 16;
	const_cast<BuildingStyle&>(HOUSE).maxResidents = 10;
	const_cast<BuildingStyle&>(HOUSE).pathableTypes.insert(1);

	const_cast<BuildingStyle&>(MILL).color = colors.orange;
	const_cast<BuildingStyle&>(MILL).size = 16;
	const_cast<BuildingStyle&>(MILL).pathableTypes.insert(1);

	const_cast<DepositStyle&>(BERRY_BUSH).color = colors.red;
	const_cast<DepositStyle&>(BERRY_BUSH).resourceType = food;
	const_cast<DepositStyle&>(BERRY_BUSH).amount = 200;
	const_cast<DepositStyle&>(BERRY_BUSH).size = 14;
	const_cast<DepositStyle&>(BERRY_BUSH).pathableTypes.insert(1);

	const_cast<DepositStyle&>(FISH).color = colors.blue;
	const_cast<DepositStyle&>(FISH).resourceType = food;
	const_cast<DepositStyle&>(FISH).amount = 200;
	const_cast<DepositStyle&>(FISH).size = 10;
	const_cast<DepositStyle&>(FISH).pathableTypes.insert(0);

	const_cast<DepositStyle&>(TREE).color = colors.brown;
	const_cast<DepositStyle&>(TREE).resourceType = wood;
	const_cast<DepositStyle&>(TREE).amount = 200;
	const_cast<DepositStyle&>(TREE).size = 12;
	const_cast<DepositStyle&>(TREE).pathableTypes.insert(1);

	const_cast<DepositStyle&>(GOLD_MINE).color = colors.yellow;
	const_cast<DepositStyle&>(GOLD_MINE).resourceType = gold;
	const_cast<DepositStyle&>(GOLD_MINE).amount = 1000;
	const_cast<DepositStyle&>(GOLD_MINE).size = 12;
	const_cast<DepositStyle&>(GOLD_MINE).pathableTypes.insert(1);

	const_cast<DepositStyle&>(STONE_MINE).color = colors.darkGrey;
	const_cast<DepositStyle&>(STONE_MINE).resourceType = stone;
	const_cast<DepositStyle&>(STONE_MINE).amount = 1000;
	const_cast<DepositStyle&>(STONE_MINE).size = 12;
	const_cast<DepositStyle&>(STONE_MINE).pathableTypes.insert(1);

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
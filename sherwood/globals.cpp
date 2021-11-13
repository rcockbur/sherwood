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
const FixedStyle* placementBuildingStyle(nullptr);
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
const FixedStyle ROCK = FixedStyle("Rock");
const FixedStyle HOUSE = FixedStyle("House");
const FixedStyle MILL = FixedStyle("Mill");
const FixedStyle BERRY_BUSH = FixedStyle("Berry Bush");
const FixedStyle FISH = FixedStyle("Fish");
const FixedStyle TREE = FixedStyle("Tree");
const FixedStyle GOLD_MINE = FixedStyle("Gold Mine");
const FixedStyle STONE_MINE = FixedStyle("Stone Mine");

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

	const_cast<FixedStyle&>(ROCK).color = colors.darkGrey;
	const_cast<FixedStyle&>(ROCK).size = 12;
	const_cast<FixedStyle&>(ROCK).pathableTypes.insert(1);

	const_cast<FixedStyle&>(HOUSE).color = colors.black;
	const_cast<FixedStyle&>(HOUSE).resources[food] = 50;
	const_cast<FixedStyle&>(HOUSE).resources[wood] = 100;
	const_cast<FixedStyle&>(HOUSE).size = 16;
	const_cast<FixedStyle&>(HOUSE).maxResidents = 10;
	const_cast<FixedStyle&>(HOUSE).pathableTypes.insert(1);

	const_cast<FixedStyle&>(MILL).color = colors.orange;
	const_cast<FixedStyle&>(MILL).size = 16;
	const_cast<FixedStyle&>(MILL).pathableTypes.insert(1);

	const_cast<FixedStyle&>(BERRY_BUSH).color = colors.red;
	const_cast<FixedStyle&>(BERRY_BUSH).resourceType = food;
	const_cast<FixedStyle&>(BERRY_BUSH).resourceCount = 200;
	const_cast<FixedStyle&>(BERRY_BUSH).size = 14;
	const_cast<FixedStyle&>(BERRY_BUSH).pathableTypes.insert(1);
			   
	const_cast<FixedStyle&>(FISH).color = colors.blue;
	const_cast<FixedStyle&>(FISH).resourceType = food;
	const_cast<FixedStyle&>(FISH).resourceCount = 200;
	const_cast<FixedStyle&>(FISH).size = 10;
	const_cast<FixedStyle&>(FISH).pathableTypes.insert(0);
			   
	const_cast<FixedStyle&>(TREE).color = colors.brown;
	const_cast<FixedStyle&>(TREE).resourceType = wood;
	const_cast<FixedStyle&>(TREE).resourceCount = 200;
	const_cast<FixedStyle&>(TREE).size = 12;
	const_cast<FixedStyle&>(TREE).pathableTypes.insert(1);
			   
	const_cast<FixedStyle&>(GOLD_MINE).color = colors.yellow;
	const_cast<FixedStyle&>(GOLD_MINE).resourceType = gold;
	const_cast<FixedStyle&>(GOLD_MINE).resourceCount = 1000;
	const_cast<FixedStyle&>(GOLD_MINE).size = 12;
	const_cast<FixedStyle&>(GOLD_MINE).pathableTypes.insert(1);
			   
	const_cast<FixedStyle&>(STONE_MINE).color = colors.darkGrey;
	const_cast<FixedStyle&>(STONE_MINE).resourceType = stone;
	const_cast<FixedStyle&>(STONE_MINE).resourceCount = 1000;
	const_cast<FixedStyle&>(STONE_MINE).size = 12;
	const_cast<FixedStyle&>(STONE_MINE).pathableTypes.insert(1);

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
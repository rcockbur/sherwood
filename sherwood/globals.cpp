#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"
#include "pathfinding.h"
#include "entity_style.h"
#include "types.h"

bool showGrid = false;
bool showPathfinding = false;
bool showPaths = false;
bool hasPrinted = false;
bool shiftIsDown = false;
int targetFPS = 30;
int tics = 0;
int seconds = 0;
float actualFPS = (float)targetFPS;
std::set<Entity*> selectedEntities;
const EntityStyle* placementEntityStyle(nullptr);
Vec2f mouseScreenPos(0, 0);
Vec2f mouseWorldPos(-1, -1);
Vec2i mouseTile(-1, -1);
Vec2f selectionStartPos = Vec2f();
bool selectionRectActive = false;

sf::Clock deltaClock;
sf::Clock gameClock;
sf::Time dt = deltaClock.restart();

const Colors colors;
Map map("data/map2.txt");
UI ui;
sf::View mapView(sf::FloatRect(Vec2f(), ui.viewportPanel.getSize()));
//sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Sherwood", sf::Style::Fullscreen);
sf::RenderWindow renderWindow(sf::VideoMode((int)ui.hud.getSize().x, (int)ui.hud.getSize().y), "Sherwood");
Graphics graphics;
EntityManager em;
AStar aStar;
BreadthFirst breadthFirst;

const EntityStyle PERSON = EntityStyle();
const EntityStyle ROCK = EntityStyle();
const EntityStyle HOUSE = EntityStyle();
const EntityStyle MILL = EntityStyle();
const EntityStyle BERRY_BUSH = EntityStyle();
const EntityStyle FISH = EntityStyle();
const EntityStyle TREE = EntityStyle();
const EntityStyle GOLD_MINE = EntityStyle();
const EntityStyle STONE_MINE = EntityStyle();

void initEntityStyles() {
	EntityStyle templateFixed = EntityStyle();
	templateFixed.isUnit = false;

	EntityStyle templateUnit = EntityStyle();
	templateUnit.isUnit = true;

	const_cast<EntityStyle&>(PERSON) = templateUnit;
	const_cast<EntityStyle&>(PERSON).name = "person";
	const_cast<EntityStyle&>(PERSON).size = ENTITY_SIZE_MEDIUM;
	const_cast<EntityStyle&>(PERSON).color = colors.purple;
	const_cast<EntityStyle&>(PERSON).pathableTypes.insert(1);
	const_cast<EntityStyle&>(PERSON).movePeriod = 1;
	const_cast<EntityStyle&>(PERSON).moveDistance = 4.0f;
	const_cast<EntityStyle&>(PERSON).carryCapacity = 10;
	const_cast<EntityStyle&>(PERSON).gatherPeriod = 7;
	const_cast<EntityStyle&>(PERSON).updateShapes();

	const_cast<EntityStyle&>(ROCK) = templateFixed;
	const_cast<EntityStyle&>(ROCK).name = "rock";
	const_cast<EntityStyle&>(ROCK).size = ENTITY_SIZE_MEDIUM;
	const_cast<EntityStyle&>(ROCK).color = colors.darkGrey;
	const_cast<EntityStyle&>(ROCK).pathableTypes.insert(1);
	const_cast<EntityStyle&>(ROCK).updateShapes();

	const_cast<EntityStyle&>(HOUSE) = templateFixed;
	const_cast<EntityStyle&>(HOUSE).name = "house";
	const_cast<EntityStyle&>(HOUSE).size = ENTITY_SIZE_LARGE;
	const_cast<EntityStyle&>(HOUSE).color = colors.black;
	const_cast<EntityStyle&>(HOUSE).pathableTypes.insert(1);
	const_cast<EntityStyle&>(HOUSE).maxResidents = 10;
	const_cast<EntityStyle&>(HOUSE).updateShapes();
	
	const_cast<EntityStyle&>(MILL) = templateFixed;
	const_cast<EntityStyle&>(MILL).name = "mill";
	const_cast<EntityStyle&>(MILL).size = ENTITY_SIZE_LARGE;
	const_cast<EntityStyle&>(MILL).color = colors.orange;
	const_cast<EntityStyle&>(MILL).pathableTypes.insert(1);
	const_cast<EntityStyle&>(MILL).updateShapes();

	const_cast<EntityStyle&>(BERRY_BUSH) = templateFixed;
	const_cast<EntityStyle&>(BERRY_BUSH).name = "berry bush";
	const_cast<EntityStyle&>(BERRY_BUSH).size = ENTITY_SIZE_MEDIUM;
	const_cast<EntityStyle&>(BERRY_BUSH).color = colors.red;
	const_cast<EntityStyle&>(BERRY_BUSH).pathableTypes.insert(1);
	const_cast<EntityStyle&>(BERRY_BUSH).resourceType = food;
	const_cast<EntityStyle&>(BERRY_BUSH).resourceCount = 200;
	const_cast<EntityStyle&>(BERRY_BUSH).updateShapes();
			   
	const_cast<EntityStyle&>(FISH) = templateFixed;
	const_cast<EntityStyle&>(FISH).name = "fish";
	const_cast<EntityStyle&>(FISH).size = ENTITY_SIZE_SMALL;
	const_cast<EntityStyle&>(FISH).color = colors.blue;
	const_cast<EntityStyle&>(FISH).pathableTypes.insert(0);
	const_cast<EntityStyle&>(FISH).resourceType = food;
	const_cast<EntityStyle&>(FISH).resourceCount = 200;
	const_cast<EntityStyle&>(FISH).updateShapes();
		   
	const_cast<EntityStyle&>(TREE) = templateFixed;
	const_cast<EntityStyle&>(TREE).name = "tree";
	const_cast<EntityStyle&>(TREE).size = ENTITY_SIZE_MEDIUM;
	const_cast<EntityStyle&>(TREE).color = colors.brown;
	const_cast<EntityStyle&>(TREE).pathableTypes.insert(1);
	const_cast<EntityStyle&>(TREE).resourceType = wood;
	const_cast<EntityStyle&>(TREE).resourceCount = 200;
	const_cast<EntityStyle&>(TREE).updateShapes();
			   
	const_cast<EntityStyle&>(GOLD_MINE) = templateFixed;
	const_cast<EntityStyle&>(GOLD_MINE).name = "gold mine";
	const_cast<EntityStyle&>(GOLD_MINE).size = ENTITY_SIZE_MEDIUM;
	const_cast<EntityStyle&>(GOLD_MINE).color = colors.yellow;
	const_cast<EntityStyle&>(GOLD_MINE).pathableTypes.insert(1);
	const_cast<EntityStyle&>(GOLD_MINE).resourceType = gold;
	const_cast<EntityStyle&>(GOLD_MINE).resourceCount = 1000;
	const_cast<EntityStyle&>(GOLD_MINE).updateShapes();
			   
	const_cast<EntityStyle&>(STONE_MINE) = templateFixed;
	const_cast<EntityStyle&>(STONE_MINE).name = "stone mine";
	const_cast<EntityStyle&>(STONE_MINE).size = ENTITY_SIZE_MEDIUM;
	const_cast<EntityStyle&>(STONE_MINE).color = colors.darkGrey;
	const_cast<EntityStyle&>(STONE_MINE).pathableTypes.insert(1);
	const_cast<EntityStyle&>(STONE_MINE).resourceType = stone;
	const_cast<EntityStyle&>(STONE_MINE).resourceCount = 1000;
	const_cast<EntityStyle&>(STONE_MINE).updateShapes();
}

void initWindow() {
	renderWindow.setPosition(Vec2i(0, 0));
	renderWindow.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(DivideVec2<float>(ui.viewportPanel.getPosition(), ui.hud.getSize()));
	Vec2f viewportSizeRatio(DivideVec2<float>(ui.viewportPanel.getSize(), ui.hud.getSize()));
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	mapView.move(Vec2f(-10, -10));
}
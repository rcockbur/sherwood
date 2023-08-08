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
float TILE_SIZE = 16;
float zoom = 1;

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
Map map("data/map1.txt");
UI ui;
sf::View mapView(sf::FloatRect(Vec2f(), ui.viewportPanel.getSize()));
//sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Sherwood", sf::Style::Fullscreen);
sf::RenderWindow renderWindow(sf::VideoMode((int)ui.hud.getSize().x, (int)ui.hud.getSize().y), "Sherwood");
Graphics graphics;
EntityManager em;
AStar aStar;
BreadthFirst breadthFirst;

EntityStyle PERSON = EntityStyle();
EntityStyle ROCK = EntityStyle();
EntityStyle HOUSE = EntityStyle();
EntityStyle MILL = EntityStyle();
EntityStyle BERRY_BUSH = EntityStyle();
EntityStyle FISH = EntityStyle();
EntityStyle TREE = EntityStyle();
EntityStyle GOLD_MINE = EntityStyle();
EntityStyle STONE_MINE = EntityStyle();

void initEntityStyles() {

	PERSON.isUnit = true;
	PERSON.isCircle = true;
	PERSON.name = "person";
	PERSON.size = ENTITY_SIZE_MEDIUM;
	PERSON.color = colors.purple;
	PERSON.pathableTypes.insert(1);
	PERSON.movePeriod = 1;
	PERSON.moveDistance = 4.0f;
	PERSON.carryCapacity = 10;
	PERSON.gatherPeriod = 7;
	PERSON.updateShapes();

	ROCK.isUnit = false;
	ROCK.isCircle = false;
	ROCK.name = "rock";
	ROCK.size = ENTITY_SIZE_MEDIUM;
	ROCK.color = colors.darkGrey;
	ROCK.pathableTypes.insert(1);
	ROCK.updateShapes();

	HOUSE.isUnit = false;
	HOUSE.isCircle = false;
	HOUSE.name = "house";
	HOUSE.size = ENTITY_SIZE_LARGE;
	HOUSE.color = colors.black;
	HOUSE.pathableTypes.insert(1);
	HOUSE.maxResidents = 10;
	HOUSE.updateShapes();
	
	MILL.isUnit = false;
	MILL.isCircle = false;
	MILL.name = "mill";
	MILL.size = ENTITY_SIZE_LARGE;
	MILL.color = colors.orange;
	MILL.pathableTypes.insert(1);
	MILL.updateShapes();

	BERRY_BUSH.isUnit = false;
	BERRY_BUSH.isCircle = false;
	BERRY_BUSH.name = "berry bush";
	BERRY_BUSH.size = ENTITY_SIZE_MEDIUM;
	BERRY_BUSH.color = colors.red;
	BERRY_BUSH.pathableTypes.insert(1);
	BERRY_BUSH.resourceType = food;
	BERRY_BUSH.resourceCount = 200;
	BERRY_BUSH.updateShapes();
	
	FISH.isUnit = false;
	FISH.isCircle = false;
	FISH.name = "fish";
	FISH.size = ENTITY_SIZE_SMALL;
	FISH.color = colors.blue;
	FISH.pathableTypes.insert(0);
	FISH.resourceType = food;
	FISH.resourceCount = 200;
	FISH.updateShapes();
	
	TREE.isUnit = false;
	TREE.isCircle = true;
	TREE.name = "tree";
	TREE.size = ENTITY_SIZE_SMALL;
	TREE.color = colors.brown;
	TREE.pathableTypes.insert(1);
	TREE.resourceType = wood;
	TREE.resourceCount = 200;
	TREE.updateShapes();
	
	GOLD_MINE.isUnit = false;
	GOLD_MINE.isCircle = false;
	GOLD_MINE.name = "gold mine";
	GOLD_MINE.size = ENTITY_SIZE_MEDIUM;
	GOLD_MINE.color = colors.yellow;
	GOLD_MINE.pathableTypes.insert(1);
	GOLD_MINE.resourceType = gold;
	GOLD_MINE.resourceCount = 1000;
	GOLD_MINE.updateShapes();
	
	STONE_MINE.isUnit = false;
	STONE_MINE.isCircle = false;
	STONE_MINE.name = "stone mine";
	STONE_MINE.size = ENTITY_SIZE_MEDIUM;
	STONE_MINE.color = colors.darkGrey;
	STONE_MINE.pathableTypes.insert(1);
	STONE_MINE.resourceType = stone;
	STONE_MINE.resourceCount = 1000;
	STONE_MINE.updateShapes();
}

void initWindow() {
	renderWindow.setPosition(Vec2i(0, 0));
	renderWindow.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(DivideVec2<float>(ui.viewportPanel.getPosition(), ui.hud.getSize()));
	Vec2f viewportSizeRatio(DivideVec2<float>(ui.viewportPanel.getSize(), ui.hud.getSize()));
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	mapView.move(Vec2f(-10, -10));
}
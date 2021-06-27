#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"
#include "pathfinding.h"
#include "entity_type.h"

bool showGrid = true;
bool showPathfinding = false;
bool hasPrinted = false;
bool shiftIsDown = false;
int targetFPS = 30;
float actualFPS = (float)targetFPS;
Entity* selectedEntity(nullptr);
int tic(0);
sf::Clock deltaClock;
sf::Time dt = deltaClock.restart();

const Colors color;
Map map("data/map.txt");
sf::View mapView(sf::FloatRect(0, 0, VIEWPORT_SIZE[0], VIEWPORT_SIZE[1]));
//sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Sherwood", sf::Style::Fullscreen);
sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE[0], WINDOW_SIZE[1]), "Sherwood");
const Vec2f GRID_SIZE((float)map.tileCount.x * TILE_SIZE, ((float)map.tileCount.y * TILE_SIZE));

Graphics graphics;
EntityManager em;
Input input;
aStar astar;


UnitType person = UnitType("person");
DoodadType rock = DoodadType("rock");
BuildingType house = BuildingType("house");
DepositType berryBush = DepositType("berry bush");
DepositType tree = DepositType("tree");

void initEntityTypes() {
	person.color = color.lightBlue;
	person.movePeriod = 1;
	person.moveDistance = 4.0f;
	person.carryCapacity = 5;
	person.gatherPeriod = 30;
	person.size = 12;

	rock.color = color.darkGrey;
	rock.size = 12;

	house.color = color.black;
	house.resources[food] = 50;
	house.resources[wood] = 100;
	house.size = 16;

	berryBush.color = color.red;
	berryBush.resourceType = food;
	berryBush.amount = 10;
	berryBush.size = 14;

	tree.color = color.brown;
	tree.resourceType = wood;
	tree.amount = 50;
	tree.size = 12;
}

void initWindow() {
	renderWindow.setPosition(Vec2i(0, 0));
	renderWindow.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(VIEWPORT_OFFSET[0] / WINDOW_SIZE[0], VIEWPORT_OFFSET[1] / WINDOW_SIZE[1]);
	Vec2f viewportSizeRatio(VIEWPORT_SIZE[0] / WINDOW_SIZE[0], VIEWPORT_SIZE[1] / WINDOW_SIZE[1]);
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	mapView.move(Vec2f(-10, -10));
}
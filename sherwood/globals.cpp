#include "globals.h"
#include "ability.h"
#include "entity.h"
#include "color.h"
#include "pathfinding.h"
#include "entity_type.h"

bool showGrid = true;
bool showPathfinding = false;
bool hasPrinted = false;
int targetFPS = 30;
float actualFPS = (float)targetFPS;
Entity* selectedEntity(nullptr);
int tic(0);
sf::Clock deltaClock;
sf::Time dt = deltaClock.restart();

const float LINE_WIDTH_HALF(0.5);
const float LINE_WIDTH(LINE_WIDTH_HALF * 2);
const float TILE_SIZE = 25;
const float ENTITY_SIZE = 18;
const float PATH_DEBUG_SIZE = 10;
const Vec2u WINDOW_SIZE(1200, 700);
const float WINDOW_PADDING_TOP(5);
const float WINDOW_PADDING_LEFT(5);
const float WINDOW_PADDING_BOT(10);
const float TOP_PANEL_HEIGHT(20);
const float VIEWPORT_WIDTH(1000);
const Vec2f VIEWPORT_SIZE(VIEWPORT_WIDTH, WINDOW_SIZE.y - WINDOW_PADDING_TOP - WINDOW_PADDING_BOT - TOP_PANEL_HEIGHT);
const Vec2f VIEWPORT_OFFSET(WINDOW_PADDING_LEFT, WINDOW_PADDING_TOP + TOP_PANEL_HEIGHT);
const sf::Rect<float> VIEWPORT_RECT(VIEWPORT_OFFSET, VIEWPORT_SIZE);
const Vec2f RIGHT_PANEL_OFFSET(VIEWPORT_OFFSET.x + VIEWPORT_SIZE.x + 3, VIEWPORT_OFFSET.y);

Map map("data/map.txt");
sf::View mapView(sf::FloatRect(0, 0, VIEWPORT_SIZE.x, VIEWPORT_SIZE.y));
//sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Sherwood", sf::Style::Fullscreen);
sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Sherwood");
const Vec2f GRID_SIZE((float)map.tileCount.x * TILE_SIZE, ((float)map.tileCount.y * TILE_SIZE));

Graphics graphics;
EntityManager em;
Input input;
aStar astar;

//const ResourceType food("food");
const std::string resourceNames[NUM_RESOURCES] = { "food", "wood" };

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

	rock.color = color.grey;

	house.color = color.black;
	house.resources[food] = 50;
	house.resources[wood] = 100;

	berryBush.color = color.red;
	berryBush.resourceType = food;
	berryBush.amount = 100;

	tree.color = color.brown;
	tree.resourceType = wood;
	tree.amount = 50;
}

void initWindow() {
	renderWindow.setPosition(Vec2i(0, 0));
	renderWindow.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(VIEWPORT_OFFSET.x / WINDOW_SIZE.x, VIEWPORT_OFFSET.y / WINDOW_SIZE.y);
	Vec2f viewportSizeRatio(VIEWPORT_SIZE.x / WINDOW_SIZE.x, VIEWPORT_SIZE.y / WINDOW_SIZE.y);
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	mapView.move(Vec2f(-10, -10));
}
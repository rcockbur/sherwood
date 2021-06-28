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

const Colors colors;
Map map("data/map.txt");
sf::View mapView(sf::FloatRect(0, 0, VIEWPORT_SIZE[0], VIEWPORT_SIZE[1]));
//sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Sherwood", sf::Style::Fullscreen);
sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE[0], WINDOW_SIZE[1]), "Sherwood");
const Vec2f GRID_SIZE((float)map.tileCount.x * TILE_SIZE, ((float)map.tileCount.y * TILE_SIZE));

Graphics graphics;
EntityManager em;
Input input;
aStar astar;

UnitType person = UnitType("Person");
DoodadType rock = DoodadType("Rock");
BuildingType house = BuildingType("House");
DepositType berryBush = DepositType("Berries");
DepositType tree = DepositType("Tree");

sf::RectangleShape FixedEntityType::shape = sf::RectangleShape();
sf::RectangleShape FixedEntityType::outlineShape = sf::RectangleShape();
sf::CircleShape UnitType::shape = sf::CircleShape();
sf::CircleShape UnitType::outlineShape = sf::CircleShape();

void initEntityTypes() {
	person.color = colors.lightBlue;
	person.movePeriod = 1;
	person.moveDistance = 4.0f;
	person.carryCapacity = 5;
	person.gatherPeriod = 15;
	person.size = 12;

	rock.color = colors.darkGrey;
	rock.size = 12;

	house.color = colors.black;
	house.resources[food] = 50;
	house.resources[wood] = 100;
	house.size = 16;

	berryBush.color = colors.red;
	berryBush.resourceType = food;
	berryBush.amount = 10;
	berryBush.size = 14;

	tree.color = colors.brown;
	tree.resourceType = wood;
	tree.amount = 50;
	tree.size = 12;

	FixedEntityType::outlineShape.setFillColor(colors.transparent);
	FixedEntityType::outlineShape.setOutlineColor(colors.yellow);
	FixedEntityType::outlineShape.setOutlineThickness(-OUTLINE_WIDTH);

	UnitType::outlineShape.setFillColor(colors.transparent);
	UnitType::outlineShape.setOutlineColor(colors.yellow);
	UnitType::outlineShape.setOutlineThickness(-OUTLINE_WIDTH);
}

void initWindow() {
	renderWindow.setPosition(Vec2i(0, 0));
	renderWindow.setFramerateLimit(targetFPS);
	Vec2f viewportOffsetRatio(VIEWPORT_OFFSET[0] / WINDOW_SIZE[0], VIEWPORT_OFFSET[1] / WINDOW_SIZE[1]);
	Vec2f viewportSizeRatio(VIEWPORT_SIZE[0] / WINDOW_SIZE[0], VIEWPORT_SIZE[1] / WINDOW_SIZE[1]);
	mapView.setViewport(sf::FloatRect(viewportOffsetRatio.x, viewportOffsetRatio.y, viewportSizeRatio.x, viewportSizeRatio.y));
	mapView.move(Vec2f(-10, -10));
}
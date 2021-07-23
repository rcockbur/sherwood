#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_style.h"
#include "pathfinding.h"
#include "globals.h"
#include "utility.h"
#include "string"
#include "job.h"
#include "entity_manager.h"

int Entity::id_index = 0;

//Entity
Entity::Entity(const EntityStyle& style, const Vec2i _tile) :
	style(style),
	id(id_index),
	tile(_tile),
	pos(tileToWorld(tile)),
	bounds(calculateBounds(pos)),
	color(style.color),
	isSelected(false)
{
	++id_index;
	map.validateWithinBounds(tile);
	validatePathable(tile);
	em.entities.insert({ this });
}

Entity::~Entity() {
	if (isSelected) {
		selectedEntity = nullptr;
	}
	em.entities.erase(this);
}

void Entity::getSelectionText(std::ostringstream& s) const {
	std::string classString(typeid(*this).name());
	classString.erase(0, 6); 
	//s << "Class: " << classString << "\n";
	s << "Type: " << style.name << "\n";
	s << "ID: " << id << "\n";
	s << "Tile: " << tile << "\n";
}

bool Entity::tileIsPathable(const Vec2i _tile) const {
	return (style.pathableTypes.find(map.terrainGrid[_tile.x][_tile.y]) != style.pathableTypes.end());
}

void Entity::validatePathable(const Vec2i _tile) const {
	if(style.pathableTypes.find(map.terrainGrid[_tile.x][_tile.y]) == style.pathableTypes.end())
		throw std::logic_error("terrain is unpathable");
}

void Entity::select() {
	if (selectedEntity)
		selectedEntity->isSelected = false;
	selectedEntity = this;
	isSelected = true;
}
void Entity::deselect() {
	if (selectedEntity == this) {
		isSelected = false;
		selectedEntity = nullptr;
	}
	else {
		throw std::logic_error("entity was not selected");
	}
}

const EntityStyle& Entity::entityType() const {
	return style;
}

Rect Entity::calculateBounds(const Vec2f& pos) const {
	return Rect(pos.x - style.size / 2, pos.y - style.size / 2, style.size, style.size);
}

bool Entity::operator==(const Lookup& lookup) const {
	return (id == lookup.id);
}

//Fixed
Fixed::Fixed(const FixedStyle& _type, const Vec2i _tile) :
	Entity(_type, _tile)
{
	map.setEntityAtTile(*this, _tile);
}

Fixed::~Fixed() {
	map.removeEntityAtTile(tile);
}

void Fixed::getSelectionText(std::ostringstream& s) const {
	Entity::getSelectionText(s);
}

const FixedStyle& Fixed::fixedEntityType() const {
	return static_cast<const FixedStyle&>(style);
}

//Doodad
Doodad::Doodad(const DoodadStyle& _type, const Vec2i _tile) :
	Fixed(_type, _tile)
{}

Doodad::~Doodad() {}

const DoodadStyle& Doodad::doodadType() const {
	return static_cast<const DoodadStyle&>(style);
}

//Deposit
Deposit::Deposit(const DepositStyle& _type, const Vec2i _tile) :
	Fixed(_type, _tile),
	amount(_type.amount)
{}

Deposit::~Deposit() {}

void Deposit::getSelectionText(std::ostringstream& s) const {
	Fixed::getSelectionText(s);
	s << std::to_string(amount) << " " << resourceNames[depositType().resourceType] << "\n";
}

const DepositStyle& Deposit::depositType() const {
	return static_cast<const DepositStyle&>(style);
}

//Building
Building::Building(const BuildingStyle& _type, const Vec2i _tile) :
	Fixed(_type, _tile),
	resources(_type.resources)
{}

void Building::getSelectionText(std::ostringstream& s) const {
	Fixed::getSelectionText(s);
	if (resources.empty() == false) {
		s << "Resources:\n";
		for (int resourceType = 0; resourceType < NUM_RESOURCES; resourceType++) {
			if (resources[resourceType] > 0) {
				s << "    " << resources[resourceType] << " " << resourceNames[resourceType] << "\n";
			}
		}
	}
}

const BuildingStyle& Building::buildingType() const {
	return static_cast<const BuildingStyle&>(style);
}

//Unit
Unit::Unit(const UnitStyle& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	canMoveAt(0),
	canGatherAt(0),
	carryAmmount(0),
	carryType(0)
{
	em.unitMap.insert({ id, this });
}

Unit::~Unit() {
	for (Job* job : jobQueue) {
		delete job;
	}
	std::cout << em.unitMap.size() << std::endl;
	em.unitMap.erase(id);
	std::cout << em.unitMap.size() << std::endl;
}

void Unit::update()
{
	if (jobQueue.size() > 0) {
		Job* job = jobQueue.front();
		CompleteStatus jobStatus = job->execute();
		if (jobStatus == CompleteStatus::complete) {
			delete job;
			jobQueue.pop_front();
		}
	}
}

void Unit::getSelectionText(std::ostringstream& s) const {
	Entity::getSelectionText(s);
	s << "Home: " << ((homeLookup.id >= 0) ? std::to_string(homeLookup.id) : "-") << "\n";
	s << "JobQueue: " << jobQueue.size() << "\n";
	s << "Carrying: ";
	if (carryAmmount > 0)
		s << std::to_string(carryAmmount) << " " << resourceNames[carryType] << "\n";
	else
		s << "-\n";
}

const UnitStyle& Unit::unitType() const {
	return static_cast<const UnitStyle&>(style);
}

void Unit::addJob(Job* job) {
	jobQueue.push_back(job);
}

void Unit::setJob(Job* job) {
	destroyJobs();
	jobQueue.push_back(job);
}

void Unit::destroyJobs() {
	for (auto job : jobQueue) delete job;
	jobQueue.clear();
}

void Unit::setHome(Building& home) {
	homeLookup = home;
}

bool Unit::moveTowards(const Vec2i targetTile) {
	Vec2f targetPos = tileToWorld(targetTile);
	Vec2f diff = targetPos - pos;
	float dist = (float)sqrt(pow(diff.x, 2) + pow(diff.y, 2));
	bool reachedTarget = false;
	if (dist > unitType().moveDistance) {
		(diff /= dist) *= unitType().moveDistance;
		pos += diff;
		
	}
	else {
		pos = targetPos;
		reachedTarget = true;
	}
	bounds = calculateBounds(pos);
	tile = worldToTile(pos);
	return reachedTarget;
}


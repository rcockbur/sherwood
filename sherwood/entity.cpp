#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_type.h"
#include "pathfinding.h"
#include "globals.h"
#include "utility.h"
#include "string"
#include "job.h"
#include "entity_manager.h"

int Entity::id_index = 0;

Entity::Entity(const EntityType& type, const Vec2i _tile) :
	type(type),
	id(id_index),
	tile(_tile),
	pos(tileToWorld(tile)),
	bounds(calculateBounds(pos)),
	color(type.color),
	isSelected(false)
{
	++id_index;
	map.validateWithinBounds(tile);
	em.entities.insert({ this });
}

Entity::~Entity() {
	if (isSelected) {
		selectedEntity = nullptr;
	}
	em.entities.erase(this);
}

void Entity::getSelectionText(std::ostringstream& s) {
	std::string classString(typeid(*this).name());
	classString.erase(0, 6); 
	//s << "Class: " << classString << "\n";
	s << "Type: " << type.name << "\n";
	s << "ID: " << id << "\n";
	s << "Tile: " << tile << "\n";
}

const EntityType& Entity::entityType() {
	return type;
}

Rect Entity::calculateBounds(const Vec2f& pos) {
	return Rect(pos.x - type.size / 2, pos.y - type.size / 2, type.size, type.size);
}

bool Entity::operator==(const Lookup& lookup) {
	return (id == lookup.id);
}

FixedEntity::FixedEntity(const FixedEntityType& _type, const Vec2i _tile) :
	Entity(_type, _tile)
{
	em.validateStaticEntityGridAvailable(tile);
	em.staticEntityGrid[tile.x][tile.y] = this;
	map.impassGrid[tile.x][tile.y] = true;
}

FixedEntity::~FixedEntity() {
	em.staticEntityGrid[tile.x][tile.y] = nullptr;
	if (map.terrainGrid[tile.x][tile.y] > 0)
		map.impassGrid[tile.x][tile.y] = false;
}

void FixedEntity::getSelectionText(std::ostringstream& s) {
	Entity::getSelectionText(s);
}

Doodad::Doodad(const DoodadType& _type, const Vec2i _tile) :
	FixedEntity(_type, _tile)
{}

Doodad::~Doodad() {}

const DoodadType& Doodad::doodadType() {
	return static_cast<const DoodadType&>(type);
}

Deposit::Deposit(const DepositType& _type, const Vec2i _tile) :
	FixedEntity(_type, _tile),
	amount(_type.amount)
{}

Deposit::~Deposit() {}

void Deposit::getSelectionText(std::ostringstream& s) {
	FixedEntity::getSelectionText(s);
	s << std::to_string(amount) << " " << resourceNames[depositType().resourceType] << "\n";
}

const DepositType& Deposit::depositType() {
	return static_cast<const DepositType&>(type);
}

Building::Building(const BuildingType& _type, const Vec2i _tile) :
	FixedEntity(_type, _tile),
	resources(_type.resources)
{}

void Building::getSelectionText(std::ostringstream& s) {
	FixedEntity::getSelectionText(s);
	if (resources.empty() == false) {
		s << "Resources:\n";
		for (int resourceType = 0; resourceType < NUM_RESOURCES; resourceType++) {
			if (resources[resourceType] > 0) {
				s << "    " << resources[resourceType] << " " << resourceNames[resourceType] << "\n";
			}
		}
	}
}

const BuildingType& Building::buildingType() {
	return static_cast<const BuildingType&>(type);
}



Unit::Unit(const UnitType& _type, const Vec2i _tile) :
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

void Unit::getSelectionText(std::ostringstream& s) {
	Entity::getSelectionText(s);
	s << "Home: " << ((homeLookup.id >= 0) ? std::to_string(homeLookup.id) : "-") << "\n";
	s << "JobQueue: " << jobQueue.size() << "\n";
	s << "Carrying: ";
	if (carryAmmount > 0)
		s << std::to_string(carryAmmount) << " " << resourceNames[carryType] << "\n";
	else
		s << "-\n";
}

const UnitType& Unit::unitType() {
	return static_cast<const UnitType&>(type);
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


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
	position(tileToWorld(tile)),
	bounds(calculateBounds(position)),
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
	s << "Class: " << classString << "\n";
	s << "Type: " << type.name << "\n";
	s << "ID: " << id << "\n";
	s << "Tile: " << tile << "\n";
	s << "Pos: " << position << "\n";
}

Rect Entity::calculateBounds(const Vec2f& pos) {
	return Rect(pos.x - type.size / 2, pos.y - type.size / 2, type.size, type.size);
}

bool Entity::operator==(const Lookup& lookup) {
	return (id == lookup.id);
}

FixedEntity::FixedEntity(const FixedEntityType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type)
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
	FixedEntity(_type, _tile),
	type(_type)
{}

Doodad::~Doodad() {}

Deposit::Deposit(const DepositType& _type, const Vec2i _tile) :
	FixedEntity(_type, _tile),
	type(_type),
	amount(type.amount)
{}

Deposit::~Deposit() {}

void Deposit::getSelectionText(std::ostringstream& s) {
	FixedEntity::getSelectionText(s);
	s << std::to_string(amount) << " " << resourceNames[type.resourceType] << "\n";
}

Building::Building(const BuildingType& _type, const Vec2i _tile) :
	FixedEntity(_type, _tile),
	type(_type),
	resources(type.resources)
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

//////////////////// UNIT ///////////////////
Unit::Unit(const UnitType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type),
	canMoveAt(0),
	canGatherAt(0),
	carryAmmount(0),
	carryType(0)
{
	em.unitMap.insert({ id, this });
}

Unit::~Unit() {
	for (Ability* ability : abilityQueue) {
		delete ability;
	}
	for (Job* job : jobQueue) {
		delete job;
	}
	em.unitMap.erase(id);
}

void Unit::update()
{
	bool finishedAnAbility = false;
	Status abilityStatus;
	if (abilityQueue.size() > 0) {
		Ability* ability = abilityQueue.front();
		abilityStatus = ability->execute();
		if (abilityStatus != inProgress) {
			delete ability;
			abilityQueue.pop_front();
			finishedAnAbility = true;
		}	
	}
	if (abilityQueue.size() == 0 && jobQueue.size() > 0) {
		Job* job = jobQueue.front();
		if (finishedAnAbility && abilityStatus == failure) {
			delete job;
			jobQueue.pop_front();
		}
		else {
			
			Status jobStatus = job->addAbility();
			if (jobStatus != inProgress) {
				delete job;
				jobQueue.pop_front();
			}
		}
	}
}

void Unit::getSelectionText(std::ostringstream& s) {
	Entity::getSelectionText(s);
	s << "Home: " << ((homeLookup.id >= 0) ? std::to_string(homeLookup.id) : "-") << "\n";
	s << "AbilityQueue: " << abilityQueue.size() << "\n";
	s << "JobQueue: " << jobQueue.size() << "\n";
	s << "Carrying: ";
	if (carryAmmount > 0) {
		s << std::to_string(carryAmmount) << " " << resourceNames[carryType] << "\n";
	}
	else {
		s << "-\n";
	}
}

void Unit::addAbility(Ability* ability) {
	abilityQueue.push_back(ability);
}

void Unit::setAbility(Ability* ability) {
	destroyAbilities();
	abilityQueue.push_back(ability);
}

void Unit::destroyAbilities() {
	for (auto ability : abilityQueue) delete ability;
	abilityQueue.clear();
}

void Unit::addJob(Job* job) {
	jobQueue.push_back(job);
}

void Unit::setJob(Job* job) {
	destroyAbilities();
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
	Vec2f diff = targetPos - position;
	float dist = (float)sqrt(pow(diff.x, 2) + pow(diff.y, 2));
	bool reachedTarget = false;
	if (dist > type.moveDistance) {
		(diff /= dist) *= type.moveDistance;
		position += diff;
		
	}
	else {
		position = targetPos;
		reachedTarget = true;
	}
	bounds = calculateBounds(position);
	tile = worldToTile(position);
	return reachedTarget;
}


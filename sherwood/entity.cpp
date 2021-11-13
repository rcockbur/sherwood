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
	id(++id_index),
	tile(_tile),
	pos(tileToWorld(tile)),
	bounds(calculateBounds(pos)),
	color(style.color),
	isSelected(false)
{
	map.validateWithinBounds(tile);
	validatePathable(tile);
	em.entities.insert({ id, this });
	
}

Entity::~Entity() {
	if (isSelected) {
		selectedEntities.erase(this);
	}
	em.entities.erase(id);
}

void Entity::getSelectionText(std::ostringstream& s) const {
	std::string classString(typeid(*this).name());
	classString.erase(0, 6); 
	s << "Type: " << style.name << "\n";
	s << "ID: " << id << "\n";
	s << "Tile: " << tile << "\n";
}

bool Entity::tileIsPathable(const Vec2i _tile) const {
	return (style.pathableTypes.find(map.terrainGrid[_tile.x][_tile.y]) != style.pathableTypes.end()
		&& map.getEntityFromTile(_tile) == nullptr);
}

void Entity::validatePathable(const Vec2i _tile) const {
	if(style.pathableTypes.find(map.terrainGrid[_tile.x][_tile.y]) == style.pathableTypes.end())
		throw std::logic_error("terrain is unpathable");
}

const int Entity::getStyleID() const {
	return style.id;
}

void Entity::select() {
	selectedEntities.insert(this);
	isSelected = true;
}
void Entity::deselect() {
	selectedEntities.erase(this);
	isSelected = false;
}

const EntityStyle& Entity::entityStyle() const {
	return style;
}

Rect Entity::calculateBounds(const Vec2f& pos) const {
	return Rect(pos.x - style.size / 2, pos.y - style.size / 2, style.size, style.size);
}

bool Entity::operator==(const Lookup& lookup) const {
	return (id == lookup.id);
}

//Fixed
Fixed::Fixed(const FixedStyle& _style, const Vec2i _tile) :
	Entity(_style, _tile),
	amount(_style.resourceCount),
	resources(_style.resources)
{
	map.setEntityAtTile(*this, _tile);

	if (&_style == &HOUSE)
		em.houses.insert({ id, this });
}

Fixed::~Fixed() {
	map.removeEntityAtTile(tile);

	if (&style == &HOUSE) {
		em.houses.erase(id);
	}
		
	for (auto& it : residents) {
		it.second->home = nullptr;
	}
}

void Fixed::getSelectionText(std::ostringstream& s) const {
	Entity::getSelectionText(s);
	if (fixedStyle().resourceType != -1)
		s << std::to_string(amount) << " " << resourceNames[fixedStyle().resourceType] << "\n";

	s << "Resources:\n";
	if (resources.empty() == false) {
		for (int resourceType = 0; resourceType < NUM_RESOURCES; resourceType++) {
			if (resources[resourceType] > 0) {
				s << "    " << resources[resourceType] << " " << resourceNames[resourceType] << "\n";
			}
		}
	}
	else {
		s << "    -\n";
	}
	if (getStyleID() == HOUSE.id) {
		s << "Residents:\n";
		if (residents.size() > 0) {
			s << "    ";
			bool isFirst = true;
			for (auto& it : residents) {
				if (isFirst == false)
					s << ", ";
				s << it.second->id;
				isFirst = false;
			}
			s << "\n";
		}
		else {
			s << "    -\n";
		}
	}
}

const FixedStyle& Fixed::fixedStyle() const {
	return static_cast<const FixedStyle&>(style);
}


//Unit
Unit::Unit(const UnitStyle& _style, const Vec2i _tile) :
	Entity(_style, _tile),
	canMoveAt(0),
	canGatherAt(0),
	carryAmmount(0),
	carryType(0)
{
	em.units.insert({ id, this });
}

Unit::~Unit() {
	for (Job* job : jobQueue) {
		delete job;
	}
	if (home != nullptr)
		(*home).residents.erase(id);
	std::cout << em.units.size() << std::endl;
	em.units.erase(id);
	std::cout << em.units.size() << std::endl;
}

void Unit::update()
{
	if (jobQueue.size() > 0) {
		Job* job = jobQueue.front();
		CompleteStatus jobStatus = job->execute(jobQueue.size() == 1);
		if (jobStatus == CompleteStatus::complete) {
			delete job;
			jobQueue.pop_front();
		}
	}
}

void Unit::getSelectionText(std::ostringstream& s) const {
	Entity::getSelectionText(s);
	s << "Home: " << ((home != nullptr) ? std::to_string((*home).id) : "-") << "\n";
	s << "JobQueue: " << jobQueue.size() << "\n";
	s << "Carrying: ";
	if (carryAmmount > 0)
		s << std::to_string(carryAmmount) << " " << resourceNames[carryType] << "\n";
	else
		s << "-\n";
}

const UnitStyle& Unit::unitStyle() const {
	return static_cast<const UnitStyle&>(style);
}

void Unit::addJob(Job* job) {
	jobQueue.push_back(job);
}

void Unit::setJob(Job* job) {
	destroyJobs();
	addJob(job);
}

void Unit::destroyJobs() {
	for (auto job : jobQueue) delete job;
	jobQueue.clear();
}

void Unit::setHome(Fixed& _home) {
	home = &_home;

	if (_home.getStyleID() != HOUSE.id)
		throw std::logic_error("only houses can have residents");
	if (getStyleID() != PERSON.id)
		throw std::logic_error("only people can be residents");
	_home.residents.insert({ id, this });
}

bool Unit::moveTowards(const Vec2i targetTile) {
	Vec2f targetPos = tileToWorld(targetTile);
	Vec2f diff = targetPos - pos;
	float dist = (float)sqrt(pow(diff.x, 2) + pow(diff.y, 2));
	bool reachedTarget = false;
	if (dist > unitStyle().moveDistance) {
		(diff /= dist) *= unitStyle().moveDistance;
		pos += diff;
		
	}
	else {
		pos = targetPos;
		reachedTarget = true;
	}
	bounds = calculateBounds(pos);
	if (targetTile != tile) {
		/*if (blockImpass) {
			map.setEntityAtTile(*this, targetTile);
		}*/

		tile = targetTile;
	}
	
	return reachedTarget;
}


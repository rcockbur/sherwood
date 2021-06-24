#include "entity.h"
#include "ability.h"
#include "map.h"
#include "entity_type.h"
#include "pathfinding.h"
#include "globals.h"
#include "utility.h"
#include "string"
#include "job.h"

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
	return Rect(pos.x - ENTITY_SIZE / 2, pos.y - ENTITY_SIZE / 2, ENTITY_SIZE, ENTITY_SIZE);
}

Doodad::Doodad(const DoodadType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type)
{}

Deposit::Deposit(const DepositType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type),
	amount(type.amount)
{}

void Deposit::getSelectionText(std::ostringstream& s) {
	Entity::getSelectionText(s);
	s << std::to_string(amount) << " " << resourceNames[type.resourceType] << "\n";
}

ComplexEntity::ComplexEntity(const ComplexEntityType& _type, const Vec2i _tile) :
	Entity(_type, _tile),
	type(_type)
{}

void ComplexEntity::getSelectionText(std::ostringstream& s) {
	Entity::getSelectionText(s);
}

Unit::Unit(const UnitType& _type, const Vec2i _tile) :
	ComplexEntity(_type, _tile),
	type(_type),
	canMoveAt(0),
	canGatherAt(0),
	home(nullptr),
	carryAmmount(0),
	carryType(0)
{}

void Unit::update()
{
	if (abilityQueue.size() > 0) {
		Ability* ability = abilityQueue.front();
		bool isComplete = ability->execute();
		if (isComplete) {
			delete ability;
			abilityQueue.pop_front();
		}	
	}
	else if (jobQueue.size() > 0) {
		Job* job = jobQueue.front();
		bool isComplete = job->addAbility();
		if (isComplete) {
			delete job;
			jobQueue.pop_front();
		}
	}
}

void Unit::getSelectionText(std::ostringstream& s) {
	ComplexEntity::getSelectionText(s);
	s << "Home: " << ((home) ? std::to_string(home->id) : "-") << "\n";
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
	abilityQueue.clear();
	abilityQueue.push_back(ability);
}

void Unit::addJob(Job* job) {
	jobQueue.push_back(job);
}

void Unit::setJob(Job* job) {
	jobQueue.clear();
	jobQueue.push_back(job);
}

void Unit::setHome(Building* _home) {
	home = _home;
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

Building::Building(const BuildingType& _type, const Vec2i _tile) :
	ComplexEntity(_type, _tile),
	type(_type),
	resources(type.resources)
{}

void Building::getSelectionText(std::ostringstream& s) {
	Entity::getSelectionText(s);
	if (resources.empty() == false) {
		s << "Resources:\n";
		for (int resourceType = 0; resourceType < NUM_RESOURCES; resourceType++) {
			if (resources[resourceType] > 0) {
				s << "    " << resources[resourceType] << " " << resourceNames[resourceType] << "\n";
			}
		}
	}

}
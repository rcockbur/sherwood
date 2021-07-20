#pragma once
#include <sstream>
#include <deque>
#include "resources.h"
#include "lookup.h"

class EntityType;
class DoodadType;
class FixedEntityType;
class UnitType;
class BuildingType;
class DepositType;
class Building;
class Job;

class Entity {
public:
	static int id_index;
	const int id;
	Vec2i tile;
	Vec2f pos;
protected:
	const EntityType& type;
public:
	Rect bounds;
	Color color;
	bool isSelected;

	Entity(const EntityType& type, const Vec2i tile);
	virtual ~Entity();
	bool operator==(const Lookup& lookup);
	virtual void getSelectionText(std::ostringstream&);
	const EntityType& entityType();
protected:
	Rect calculateBounds(const Vec2f& pos);
};

class FixedEntity : public Entity {
public:
	FixedEntity(const FixedEntityType&, const Vec2i tile);
	~FixedEntity();
	virtual void getSelectionText(std::ostringstream&);
};

class Doodad : public FixedEntity {
public:
	Doodad(const DoodadType&, const Vec2i tile);
	~Doodad();
	const DoodadType& doodadType();
};

class Deposit : public FixedEntity {
public:
	int amount;

	Deposit(const DepositType& type, const Vec2i tile);
	~Deposit();
	void getSelectionText(std::ostringstream&);
	const DepositType& depositType();
};

class Building : public FixedEntity {
public:
	Resources resources;

	Building(const BuildingType& type, const Vec2i tile);
	void getSelectionText(std::ostringstream&);
	const BuildingType& buildingType();
};


class Unit : public Entity {
public:
	std::deque<Job*> jobQueue;
	int canMoveAt;
	int canGatherAt;
	Lookup homeLookup;
	int carryType;
	int carryAmmount;

	Unit(const UnitType& type, const Vec2i tile);
	~Unit();
	void update();
	void getSelectionText(std::ostringstream&);
	void addJob(Job* job);
	void setJob(Job* job);
	void destroyJobs();
	void setHome(Building& home);
	bool moveTowards(const Vec2i targetTile);
	const UnitType& unitType();
};



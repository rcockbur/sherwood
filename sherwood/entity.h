#pragma once
#include <sstream>
#include <deque>
#include "resources.h"
#include "lookup.h"

class EntityStyle;
class DoodadStyle;
class FixedStyle;
class UnitStyle;
class BuildingStyle;
class DepositStyle;
class Building;
class Job;
class Unit;

class Entity {
public:
	static int id_index;
	const int id;
	Vec2i tile;
	Vec2f pos;
protected:
	const EntityStyle& style;
public:
	Rect bounds;
	Color color;
	bool isSelected;

	Entity(const EntityStyle& style, const Vec2i tile);
	virtual ~Entity();
	bool operator==(const Lookup& lookup) const;
	bool tileIsPathable(const Vec2i tile) const;
	void validatePathable(const Vec2i tile) const;
	void select();
	void deselect();
	const int getStyleID() const;
	virtual void getSelectionText(std::ostringstream&) const;
	const EntityStyle& entityStyle() const;
protected:
	Rect calculateBounds(const Vec2f& pos) const;
};

class Fixed : public Entity {
public:
	//deposit
	int amount;

	//building
	Resources resources;
	UnitGroup residents;

	Fixed(const FixedStyle&, const Vec2i tile);
	~Fixed();
	virtual void getSelectionText(std::ostringstream&) const;
	const FixedStyle& fixedStyle() const;
};

class Unit : public Entity {
public:
	std::deque<Job*> jobQueue;
	int canMoveAt;
	int canGatherAt;
	Fixed* home;
	int carryType;
	int carryAmmount;

	Unit(const UnitStyle& style, const Vec2i tile);
	~Unit();
	void update();
	void getSelectionText(std::ostringstream&) const;
	void addJob(Job* job);
	void setJob(Job* job);
	void destroyJobs();
	void setHome(Fixed& home);
	bool moveTowards(const Vec2i targetTile);
	const UnitStyle& unitStyle() const;
};



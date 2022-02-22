#pragma once
#include <sstream>
#include <deque>
#include "resources.h"
#include "lookup.h"

class EntityStyle;
class Job;

class Entity {
public:
	static int id_index;
	const int id;
	Vec2i tile;
	Vec2f pos;
	const EntityStyle& style;
public:
	Rect bounds;
	Color color;
	bool isSelected;
	bool isGarrisoned;
	int amount;
	Resources resources;
	EntityGroup residents;
	//UNIT
	std::deque<Job*> jobQueue;
	int canMoveAt;
	int canGatherAt;
	Entity* home;
	int carryType;
	int carryAmmount;

	Entity(const EntityStyle& style, const Vec2i tile);
	virtual ~Entity();
	bool operator==(const Lookup& lookup) const;
	bool tileIsPathable(const Vec2i tile) const;
	void validatePathable(const Vec2i tile) const;
	void select();
	void deselect();
	void garrison(Entity& target);
	void ungarrison();
	const int getStyleID() const;
	void getSelectionText(std::ostringstream&) const;
	void update();
	void addJob(Job* job);
	void setJob(Job* job);
	void destroyJobs();
	void setHome(Entity& home);
	bool moveTowards(const Vec2i targetTile);
protected:
	Rect calculateBounds(const Vec2f& pos) const;
};
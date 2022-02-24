#pragma once
#include "types.h"
#include <list>
#include "lookup.h"

class Ability {
public:
	virtual ActivityStatus execute(bool isLastJob) = 0;
	virtual std::list<Vec2i>* getPath() = 0;
};

class Move : public Ability {
public:
	Move(Entity& unit, Vec2i dest, std::list<Vec2i>&& path);
	ActivityStatus execute(bool isLastJob) override;
	std::list<Vec2i>* getPath();
protected:
	Entity& unit;
	const Vec2i dest;
	std::list<Vec2i> path;
	void followPath();
};

class Harvest : public Move {
public:
	Harvest(Entity& unit, Lookup depositLookup, std::list<Vec2i>&& path);
	ActivityStatus execute(bool isLastJob) override;
private:
	const Lookup depositLookup;
	bool hasStartedHarvesting;
};

class ReturnResources : public Move {
public :
	ReturnResources(Entity& unit, Lookup buildingLookup, std::list<Vec2i>&& path);
	ActivityStatus execute(bool isLastJob) override;
private:
	const Lookup houseLookup;
};

class Garrison : public Move {
public :
	Garrison(Entity& unit, Lookup buildingLookup, std::list < Vec2i>&& path);
	ActivityStatus execute(bool isLastJob) override;
private:
	const Lookup buildingLookup;
};
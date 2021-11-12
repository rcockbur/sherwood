#pragma once
#include "types.h"
#include "resources.h"
#include <set>

class EntityStyle {
public:
	static int id_index;
	std::string name;
	Color color;	
	float size;
	const int id;
	std::set<int> pathableTypes;
	EntityStyle(std::string&&);
	virtual Shape* getShape(const Vec2f graphicalPosition) const = 0;
	virtual Shape* getOutlineShape(const Vec2f graphicalPosition) const = 0;
};

class FixedStyle : public EntityStyle {
public:
	static RectangleShape shape;
	static RectangleShape outlineShape;

	FixedStyle(std::string&& _name);
	Shape* getShape(const Vec2f graphicalPosition) const;
	Shape* getOutlineShape(const Vec2f graphicalPosition) const;
};

class DoodadStyle: public FixedStyle {
public:
	DoodadStyle(std::string&& _name);
};

class DepositStyle : public FixedStyle {
public:
	int resourceType;
	int amount;

	DepositStyle(std::string&& _name);
};

class BuildingStyle : public FixedStyle {
public:
	Resources resources;
	int maxResidents;
	BuildingStyle(std::string&& _name);
};

class UnitStyle : public EntityStyle {
public:
	static CircleShape shape;
	static CircleShape outlineShape;

	int movePeriod;
	float moveDistance;
	int carryCapacity;
	int gatherPeriod;

	UnitStyle(std::string&& _name);
	Shape* getShape(const Vec2f graphicalPosition) const;
	Shape* getOutlineShape(const Vec2f graphicalPosition) const;
};




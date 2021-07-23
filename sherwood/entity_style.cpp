#include "entity_style.h"
#include "types.h"
#include "graphics.h"
#include "globals.h"

//Entity
EntityStyle::EntityStyle(std::string&& _name) : 
	name(std::move(_name)),
	size(TILE_SIZE)
{}

//Fixed
FixedStyle::FixedStyle(std::string&& _name) :
	EntityStyle(std::move(_name))
{}

Shape* FixedStyle::getShape(const Vec2f graphicalPosition) const {
	shape.setSize(Vec2f(size, size));
	shape.setFillColor(color);
	shape.setPosition(graphicalPosition);
	return &shape;
}

Shape* FixedStyle::getOutlineShape(const Vec2f graphicalPosition) const {
	outlineShape.setSize(Vec2f(size, size));
	outlineShape.setPosition(graphicalPosition);
	return &outlineShape;
}

//Doodad
DoodadStyle::DoodadStyle(std::string&& _name) :
	FixedStyle(std::move(_name))
{}

//Deposit
DepositStyle::DepositStyle(std::string&& _name) :
	FixedStyle(std::move(_name)),
	resourceType(0),
	amount(0)
{}

//Building
BuildingStyle::BuildingStyle(std::string&& _name) :
	FixedStyle(std::move(_name))
{}

//Unit
UnitStyle::UnitStyle(std::string&& _name) :
	EntityStyle(std::move(_name)),
	movePeriod(0),
	moveDistance(0.0f),
	carryCapacity(0),
	gatherPeriod(0)
{}

Shape* UnitStyle::getShape(const Vec2f graphicalPosition) const {
	shape.setRadius(size / 2);
	shape.setFillColor(color);
	shape.setPosition(graphicalPosition);
	return &shape;
}

Shape* UnitStyle::getOutlineShape(const Vec2f graphicalPosition) const {
	outlineShape.setRadius(size / 2);
	outlineShape.setPosition(graphicalPosition);
	return &outlineShape;
}

#include "entity_type.h"
#include "types.h"
#include "graphics.h"
#include "globals.h"

EntityType::EntityType(std::string&& _name) : 
	name(std::move(_name)),
	size(TILE_SIZE)
{}

FixedEntityType::FixedEntityType(std::string&& _name) :
	EntityType(std::move(_name))
{}

sf::Shape* FixedEntityType::getShape(const Vec2f graphicalPosition) const {
	shape.setSize(Vec2f(size, size));
	shape.setFillColor(color);
	shape.setPosition(graphicalPosition);
	return &shape;
}

sf::Shape* FixedEntityType::getOutlineShape(const Vec2f graphicalPosition) const {
	outlineShape.setSize(Vec2f(size, size));
	outlineShape.setPosition(graphicalPosition);
	return &outlineShape;
}

DoodadType::DoodadType(std::string&& _name) :
	FixedEntityType(std::move(_name))
{}

DepositType::DepositType(std::string&& _name) :
	FixedEntityType(std::move(_name)),
	resourceType(0),
	amount(0)
{}

BuildingType::BuildingType(std::string&& _name) :
	FixedEntityType(std::move(_name))
{}

UnitType::UnitType(std::string&& _name) :
	EntityType(std::move(_name)),
	movePeriod(0),
	moveDistance(0.0f),
	carryCapacity(0),
	gatherPeriod(0)
{}

sf::Shape* UnitType::getShape(const Vec2f graphicalPosition) const {
	shape.setRadius(size / 2);
	shape.setFillColor(color);
	shape.setPosition(graphicalPosition);
	return &shape;
}

sf::Shape* UnitType::getOutlineShape(const Vec2f graphicalPosition) const {
	outlineShape.setRadius(size / 2);
	outlineShape.setPosition(graphicalPosition);
	return &outlineShape;
}

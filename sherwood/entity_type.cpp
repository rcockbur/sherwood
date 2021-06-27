#include "entity_type.h"
#include "types.h"
#include "graphics.h"
#include "globals.h"

sf::RectangleShape FixedEntityType::shape = sf::RectangleShape();
sf::RectangleShape FixedEntityType::outlineShape = sf::RectangleShape();
sf::CircleShape UnitType::shape = sf::CircleShape();
sf::CircleShape UnitType::outlineShape = sf::CircleShape();

EntityType::EntityType(std::string&& _name) : 
	name(std::move(_name)),
	size(TILE_SIZE)
{}

FixedEntityType::FixedEntityType(std::string&& _name) :
	EntityType(std::move(_name))
{}

sf::Shape* FixedEntityType::getShape() const {
	return &shape;
}

sf::Shape* FixedEntityType::getOutlineShape() const {
	return &outlineShape;
}

void FixedEntityType::updateShapeSize() const {
	shape.setSize(Vec2f(size, size));
}

void FixedEntityType::updateOutlineShapeSize() const {
	outlineShape.setSize(Vec2f(size, size));
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

sf::Shape* UnitType::getShape() const {
	return &shape;
}

sf::Shape* UnitType::getOutlineShape() const {
	return &outlineShape;
}

void UnitType::updateShapeSize() const {
	shape.setRadius(size / 2);
}

void UnitType::updateOutlineShapeSize() const {
	outlineShape.setRadius(size / 2);
}
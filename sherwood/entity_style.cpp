#include "entity_style.h"
#include "types.h"
#include "graphics.h"
#include "globals.h"
#include "color.h"

int EntityStyle::id_index = 0;

//Entity
EntityStyle::EntityStyle() : 
	isUnit(false),
	size(TILE_SIZE),
	id(++id_index),
	resourceType(-1),
	resourceCount(0),
	maxResidents(0),
	movePeriod(0),
	moveDistance(0.0f),
	carryCapacity(0),
	gatherPeriod(0),
	shape(nullptr),
	outlineShape(nullptr)
{}

void EntityStyle::updateShapes() {
	if (isUnit) {
		shape = new CircleShape();
		outlineShape = new CircleShape();
		static_cast<CircleShape*>(shape)->setRadius(size / 2);
		static_cast<CircleShape*>(outlineShape)->setRadius(size / 2);
	}
	else {
		shape = new RectangleShape();
		outlineShape = new RectangleShape();
		static_cast<RectangleShape*>(shape)->setSize(Vec2f(size, size));
		static_cast<RectangleShape*>(outlineShape)->setSize(Vec2f(size, size));
	}
	outlineShape->setFillColor(colors.transparent);
	outlineShape->setOutlineColor(colors.lightYellow);
	outlineShape->setOutlineThickness(-OUTLINE_WIDTH);
	shape->setFillColor(color);
}

Shape* EntityStyle::getShape(const Vec2f graphicalPosition) const {
	shape->setPosition(graphicalPosition);
	return shape;
}

Shape* EntityStyle::getOutlineShape(const Vec2f graphicalPosition) const {
	outlineShape->setPosition(graphicalPosition);
	return outlineShape;
}
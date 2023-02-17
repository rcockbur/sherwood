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
{
	em.all_styles.insert(this);
}

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

bool EntityStyle::tileIsPathable(const Vec2i _tile) const {
	return (pathableTypes.find(map.terrainGrid[_tile.x][_tile.y]) != pathableTypes.end()
		&& map.getEntityFromTile(_tile) == nullptr);
}

Shape* EntityStyle::getShape(const Vec2f graphicalPosition, bool tintRed) const {
	shape->setPosition(graphicalPosition);
	if (tintRed) {
		shape->setFillColor(colors.red);
	}
	else {
		shape->setFillColor(color);
	}
	return shape;
}

Shape* EntityStyle::getOutlineShape(const Vec2f graphicalPosition) const {
	outlineShape->setPosition(graphicalPosition);
	return outlineShape;
}

void EntityStyle::updateSize() {
	size = TILE_SIZE;
	if (isUnit) {
		static_cast<CircleShape*>(shape)->setRadius(size / 2);
		static_cast<CircleShape*>(outlineShape)->setRadius(size / 2);
	}
	else {
		static_cast<RectangleShape*>(shape)->setSize(Vec2f(size, size));
		static_cast<RectangleShape*>(outlineShape)->setSize(Vec2f(size, size));
	}
}
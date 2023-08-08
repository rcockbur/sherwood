#pragma once
#include "types.h"
#include "resources.h"
#include <set>
#include <SFML/Graphics/Sprite.hpp>

class EntityStyle {
public:
	static int id_index;
	std::string name;
	Color color;	
	bool isUnit;
	bool isCircle;
	Shape* shape;
	Shape* outlineShape;
	float size;
	int id;
	std::set<int> pathableTypes;
	//FIXED
	//deposit
	int resourceType;
	int resourceCount;
	//building
	Resources resources;
	int maxResidents;
	//UNIT
	int movePeriod;
	float moveDistance;
	int carryCapacity;
	int gatherPeriod;
	EntityStyle();
	void updateShapes();
	bool tileIsPathable(const Vec2i tile) const;
	Shape* getShape(const Vec2f graphicalPosition, bool tintRed) const;
	Shape* getOutlineShape(const Vec2f graphicalPosition) const;
	void updateSize();
	
};


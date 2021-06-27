#pragma once
#include "types.h"
#include "resources.h"

class EntityType {
public:
	std::string name;
	sf::Color color;	
	float size;
	EntityType(std::string&&);
	virtual sf::Shape* getShape() const = 0;
	virtual sf::Shape* getOutlineShape() const = 0;
	virtual void updateShapeSize() const = 0;
	virtual void updateOutlineShapeSize() const = 0;
};

class FixedEntityType : public EntityType {
public:
	static sf::RectangleShape shape;
	static sf::RectangleShape outlineShape;

	FixedEntityType(std::string&& _name);
	sf::Shape* getShape() const;
	sf::Shape* getOutlineShape() const;
	void updateShapeSize() const;
	void updateOutlineShapeSize() const;
};

class DoodadType: public FixedEntityType {
public:
	DoodadType(std::string&& _name);
};

class DepositType : public FixedEntityType {
public:
	int resourceType;
	int amount;

	DepositType(std::string&& _name);
};

class BuildingType : public FixedEntityType {
public:
	Resources resources;

	BuildingType(std::string&& _name);
};

class UnitType : public EntityType {
public:
	static sf::CircleShape shape;
	static sf::CircleShape outlineShape;
	int movePeriod;
	float moveDistance;
	int carryCapacity;
	int gatherPeriod;

	UnitType(std::string&& _name);
	sf::Shape* getShape() const;
	sf::Shape* getOutlineShape() const;
	void updateShapeSize() const;
	void updateOutlineShapeSize() const;
};




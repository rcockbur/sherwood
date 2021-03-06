#pragma once
#include "types.h"
#include <list>


class BuildingStyle;

class Padding {
public:
	float left, top, right, bot;
	Padding();
	Padding(float left, float top, float right, float bot);
	Vec2f topLeft() const;
};

class Panel : public sf::Drawable {
public:
	Vec2f getPosition() const;
	Vec2f getInnerPosition() const;
	Vec2f getSize() const;
	BuildingStyle* getBuildingStyle() const;
	void setString(const std::string& string);
	void setBuildingStyle(BuildingStyle* BuildingType);
	void setCallback(void (*callback)(const Panel& panel, bool left, bool down));
	void handleClick(bool left, bool down);
	bool containsScreenPos(const Vec2f pos);
private:
	BuildingStyle* buildingStyle;
	std::string name;
	void (*callback)(const Panel&, bool, bool);
	Panel* parent;
	Vec2f pos;
	Vec2f size;
	Vec2f offset;
	Padding padding;
	Padding margin;
	std::list<Panel*> children;
	sf::Text text;
	RectangleShape border;
	bool drawBorder;
	Panel();
	void draw(sf::RenderTarget& target, sf::RenderStates) const;
	void setName(const std::string& name);
	void setSize(const Vec2f size);
	void setPosition(const Vec2f pos);

	void setPadding(const Padding padding);
	void setMargin(const Padding margin);
	void setParent(Panel& parent);
	void moveBelowPanel(const Panel& other);
	void moveRightOfPanel(const Panel& other);
	void updatePositionRelativeToParent();
	void setBorderColor(const Color& color);


	friend class UI;
};

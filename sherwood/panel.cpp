#include "panel.h"
#include "globals.h"
#include "color.h"

Padding::Padding() :
	left(0), top(0), right(0), bot(0) 
{}

Padding::Padding(float left, float top, float right, float bot) :
	left(left), top(top), right(right), bot(bot)
{}

Vec2f Padding::topLeft() const {
	return Vec2f(left, top);
}

Vec2f Panel::getPosition() const {
	return pos;
}

Vec2f Panel::getInnerPosition() const {
	return (pos + padding.topLeft());
}

Vec2f Panel::getSize() const {
	return size;
}

BuildingType* Panel::getBuildingType() const {
	return buildingType;
}

Panel::Panel() :
	parent(nullptr),
	drawBorder(false),
	callback(nullptr)
{
	text.setFont(ui.font);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);

	border.setOutlineThickness(-1);
	border.setFillColor(colors.transparent);
}


void Panel::draw(sf::RenderTarget& target, sf::RenderStates) const {
	for (auto childPanel : children) {
		target.draw(*childPanel);
	}
	if (text.getString().getSize() > 0)
		target.draw(text);

	if (drawBorder) target.draw(border);
}

void Panel::setName(const std::string& _name) {
	name = _name;
}

void Panel::setSize(const Vec2f _size) {
	size = _size;
	if (size.x == -1)
		size.x = parent->size.x - parent->padding.left - parent->padding.right - offset.x;
	if (size.y == -1)
		size.y = parent->size.y - parent->padding.top - parent->padding.bot - offset.y;
	border.setSize(size);
}

void Panel::setParent(Panel& _parent) {
	parent = &_parent;
	parent->children.push_back(this);
	setPosition(parent->getInnerPosition());
}

void Panel::setPosition(const Vec2f _pos) {
	pos = _pos;
	border.setPosition(pos);
	for (auto child : children) {
		child->setPosition(getInnerPosition() + child->offset);
	}
	text.setPosition(pos + padding.topLeft());
}

void Panel::setBuildingType(BuildingType* _buildingType){
	buildingType = _buildingType;
}

void Panel::setString(const std::string& string) {
	text.setString(string);
	text.setPosition(getInnerPosition());
}

void Panel::setPadding(const Padding _padding) {
	padding = _padding;
	for (auto child : children) {
		child->updatePositionRelativeToParent();
	}
	text.setPosition(getInnerPosition());
}


void Panel::moveRightOfPanel(const Panel& other) {
	if (parent == nullptr) throw std::logic_error("panel has no parent");
	if (parent != other.parent) throw std::logic_error("panels must have same parent");
	offset.x = other.offset.x + other.size.x;
	updatePositionRelativeToParent();
}

void Panel::moveBelowPanel(const Panel& other) {
	if (parent == nullptr) throw std::logic_error("panel has no parent");
	if (parent != other.parent) throw std::logic_error("panels must have same parent");
	offset.y = other.offset.y + other.size.y;
	updatePositionRelativeToParent();
}

void Panel::updatePositionRelativeToParent() {
	if (parent == nullptr) throw std::logic_error("panel has no parent");
	setPosition(parent->getInnerPosition() + offset);
}

void Panel::setBorderColor(const Color& color) {
	drawBorder = true;
	border.setOutlineColor(color);
}

void Panel::handleClick(const bool isLeftClick) {
	if (callback != nullptr) {
		callback(*this, isLeftClick);
	}
	for (auto child : children) {
		if (child->containsScreenPos(mouseScreenPos)) 
			child->handleClick(isLeftClick);
	}
}

void Panel::setCallback(void (*_callback)(const Panel&, const bool)) {
	callback = _callback;
}

bool Panel::containsScreenPos(const Vec2f _pos) {
	return (_pos.x >= pos.x && _pos.x < pos.x + size.x && _pos.y >= pos.y && _pos.y < pos.y + size.y);
}


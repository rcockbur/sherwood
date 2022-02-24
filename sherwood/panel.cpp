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

const EntityStyle* Panel::getEntityStyle() const {
	return entityStyle;
}

Panel::Panel() :
	parent(nullptr),
	entityStyle(nullptr),
	drawBorder(false),
	callback(nullptr)
{
	text.setFont(ui.font);
	text.setCharacterSize(12);
	text.setFillColor(colors.white);

	border.setOutlineThickness(-1);
	border.setFillColor(colors.transparent);

	borderActive.setOutlineThickness(-1);
	borderActive.setFillColor(colors.yellow);
	borderActive.setOutlineColor(colors.white);
}


void Panel::draw(sf::RenderTarget& target, sf::RenderStates) const {
	for (auto childPanel : children) {
		target.draw(*childPanel);
	}
	
	const RectangleShape* chosenShape;
	if ((setting != nullptr && *setting == true) || 
		(entityStyle != nullptr && placementEntityStyle == entityStyle)) {
		chosenShape = &borderActive;
	}
	else {
		chosenShape = &border;
	}
	if (drawBorder) {
		target.draw(*chosenShape);
	}
	if (text.getString().getSize() > 0)
		target.draw(text);
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
	borderActive.setSize(size);
}

void Panel::setParent(Panel& _parent) {
	parent = &_parent;
	parent->children.push_back(this);
	setPosition(parent->getInnerPosition());
}

void Panel::setPosition(const Vec2f _pos) {
	pos = _pos;
	border.setPosition(pos);
	borderActive.setPosition(pos);
	for (auto child : children) {
		child->setPosition(getInnerPosition() + child->offset);
	}
	text.setPosition(pos + padding.topLeft());
}

void Panel::setentityStyle(const EntityStyle* _entityStyle){
	entityStyle = _entityStyle;
}

void Panel::setSetting(bool* _setting) {
	setting = _setting;
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

void Panel::setMargin(const Padding _margin) {
	margin = _margin;
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

void Panel::handleClick(bool left, bool down) {
	if (callback != nullptr) {
		callback(*this, left, down);
	}
	for (auto child : children) {
		if (child->containsScreenPos(mouseScreenPos)) 
			child->handleClick(left, down);
	}
}

void Panel::setCallback(void (*_callback)(const Panel& panel, bool left, bool right)) {
	callback = _callback;
}

bool Panel::containsScreenPos(const Vec2f _pos) {
	return (_pos.x >= pos.x && _pos.x < pos.x + size.x && _pos.y >= pos.y && _pos.y < pos.y + size.y);
}


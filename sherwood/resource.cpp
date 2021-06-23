#include "resource.h"


Resources::Resources() :
	amounts{0}
{

}

Resources::Resources(const int type, int amount) :
	amounts{ 0 }
{
	amounts[type] = amount;
}

Resources::Resources(const Resources& other) {
	std::copy(other.amounts, other.amounts + NUM_RESOURCES, amounts);
}

Resources& Resources::operator=(const Resources& other) {
	std::copy(other.amounts, other.amounts + NUM_RESOURCES, amounts);
	return *this;
}

Resources Resources::operator-(const Resources& other) {
	Resources r = Resources(*this);
	for (int i = 0; i < NUM_RESOURCES; ++i) {
		r[i] -= other[i];
	}
	return r;
}

//standard index operator
int& Resources::operator[](const int type) {
	if (type < 0 || type >= NUM_RESOURCES) {
		throw std::logic_error("resource type is invalid");
	}
	return amounts[type];
}

//index operator for fetching value from const objects
const int& Resources::operator[](const int type) const {
	if (type < 0 || type >= NUM_RESOURCES) {
		throw std::logic_error("resource type is invalid");
	}
	return amounts[type];
}
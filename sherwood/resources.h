#pragma once
#include "types.h"
#include "constants.h"

class Resources {
public:
	int amounts[NUM_RESOURCES];

	Resources();
	Resources(const int type, int amount);
	Resources(const Resources& other);
	Resources& operator=(const Resources& other);
	Resources operator-(const Resources& other);
	int& operator[](const int index);
	const int& operator[](const int index) const;
	bool empty() const;

};
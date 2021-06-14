#pragma once
#include "types.h"

class ResourceType {
public:
	std::string name;
	ResourceType(const std::string name);
};

class Resource {
public:
	const ResourceType& type;
	int amount;
	Resource(const ResourceType& resourceType, int amount);
};
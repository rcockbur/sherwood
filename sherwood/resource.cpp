#include "resource.h"

ResourceType::ResourceType(const std::string _name) :
	name(_name)
{
}

Resource::Resource(const ResourceType& _type, int _amount) :
	type(_type),
	amount(_amount)
{
}


#include "Reflection/BPClass.h"

BPClass::~BPClass()
{
	auto it = Properties.begin();
	while (it != Properties.end())
	{
		auto val = it->second;
		delete val;
		++it;
	}
	Properties.clear();
}

void BPClass::AddProperty(AbstractProperty* property)
{
	Properties[std::hash<std::string>{}(property->PropertyName)] = property;
}



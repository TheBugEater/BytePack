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

void BPClass::AddProperty(BPProperty* property)
{
	Properties[std::hash<std::string>{}(property->GetName())] = property;

	property->OwnerClass = this;

	property->Next = PropertyHead;
	PropertyHead = property;
}

void BPClass::Serialize(class IBPStream* stream, class BPObject* Object)
{
	if(SuperClass)
		SuperClass->Serialize(stream, Object);

	BPProperty* Property = PropertyHead;
	while (Property)
	{
		Property->SerializeProperty(*stream, Object);
		Property = Property->Next;
	}
}

void BPClass::Deserialize(class IBPStream* stream, class BPObject* Object)
{
	if(SuperClass)
		SuperClass->Deserialize(stream, Object);
}



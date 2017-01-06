#pragma once
#ifndef __BP_CLASS_BUILDER_H__
#define __BP_CLASS_BUILDER_H__

#include "Reflection/BPProperty.h"
#include "Reflection/BPClass.h"

#define DEFINE_PROPERTY_BUILD_TYPE(type) \
void AddProperty(type dummy, size_t offset, uint32 size, std::string name, std::string description, uint32 flags = 2) \
{ \
	Properties.push_back(new BPPropertyT<type>(offset, size, name, description, flags)); \
}

template<class T>
class BPClassBuilder
{
public:
	BPClassBuilder(BPClass* classObject)
		: ClassObject(classObject)
	{

	}
	
	DEFINE_PROPERTY_BUILD_TYPE(uint8)
	DEFINE_PROPERTY_BUILD_TYPE(uint16)
	DEFINE_PROPERTY_BUILD_TYPE(uint32)
	DEFINE_PROPERTY_BUILD_TYPE(uint64)
	DEFINE_PROPERTY_BUILD_TYPE(int8)
	DEFINE_PROPERTY_BUILD_TYPE(int16)
	DEFINE_PROPERTY_BUILD_TYPE(int32)
	DEFINE_PROPERTY_BUILD_TYPE(int64)
	DEFINE_PROPERTY_BUILD_TYPE(float)
	DEFINE_PROPERTY_BUILD_TYPE(double)
	DEFINE_PROPERTY_BUILD_TYPE(bool)
	DEFINE_PROPERTY_BUILD_TYPE(char)
	DEFINE_PROPERTY_BUILD_TYPE(BPObject*)

	void AddProperty(std::string dummy, size_t offset, uint32 size, std::string name, std::string description, uint32 flags)
	{
		Properties.push_back(new BPPropertyT<std::string>(offset, size, name, description, flags)); 
	}

	template<typename MemberType>
	BPClassBuilder<T>& Property(MemberType T::* member, std::string name, std::string description, uint32 flags = 2)
	{ 
		AddProperty(MemberType(), OffsetOf(member), sizeof(std::remove_pointer<MemberType>::type), name, description, flags);
		return *this;
	}

	BPClass* Build()
	{
		for (unsigned i = 0; i < Properties.size(); i++)
		{
			ClassObject->AddProperty(Properties[i]);
		}
		return ClassObject;
	}

private:
	BPClass* ClassObject;

	std::vector<BPProperty*> Properties;
};



#endif

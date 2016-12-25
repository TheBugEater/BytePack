#pragma once
#ifndef __BP_PROPERTY_H__
#define __BP_PROPERTY_H__
#include "../BPVariant.h"

class AbstractProperty
{
public:
	virtual ~AbstractProperty() {}

	std::string PropertyName;
	std::string PropertyDescription;
	unsigned int PropertyFlags;
};

template<class ClassType>
class ObjectProperty : public AbstractProperty
{
public:
	ObjectProperty(std::string name, std::string description, unsigned int flags)
	{
		PropertyName = name;
		PropertyDescription = description;
		PropertyFlags = flags;
	}

	virtual BPSmartPtr<BPVariant>& GetValue(ClassType* object) = 0;
	virtual void SetValue(BPSmartPtr<BPVariant>& value, ClassType* object) = 0;
};

template<class ClassType, class MemberType>
class MemberProperty : public ObjectProperty<ClassType>
{
public:

	typedef MemberType ClassType::* MemberPointer;
	MemberProperty(MemberPointer member, std::string name, std::string description, unsigned int flags)
		: ObjectProperty<ClassType>(name, description, flags)
		, Member(member)
	{

	}

	virtual BPSmartPtr<BPVariant>& GetValue(ClassType* object) override
	{
		BPVariant* value = new BPVariant();
		value->SetValue<MemberType>(object->*Member);
		return BPSmartPtr<BPVariant>(value);
	}

	virtual void SetValue(BPSmartPtr<BPVariant>& value, ClassType* object) override
	{
		object->*Member = value->GetValue<MemberType>();
	}

	MemberPointer Member;
};

#endif

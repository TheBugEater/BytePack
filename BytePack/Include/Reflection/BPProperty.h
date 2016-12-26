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
	ValueTypes ValueType;

	AbstractProperty(std::string name, std::string description, unsigned int flags)
	{
		PropertyName = name;
		PropertyDescription = description;
		PropertyFlags = flags;
	}

	virtual BPSmartPtr<BPVariant> GetValue(BPObject* object) = 0;
	virtual void SetValue(BPSmartPtr<BPVariant> value, BPObject* object) = 0;
};

template<class ClassType, class MemberType>
class MemberProperty : public AbstractProperty
{
public:

	typedef MemberType ClassType::* MemberPointer;
	MemberProperty(MemberPointer member, std::string name, std::string description, unsigned int flags)
		: AbstractProperty(name, description, flags)
		, Member(member)
	{
		ValueType = ToValueType<MemberType>();
	}

	virtual BPSmartPtr<BPVariant> GetValue(BPObject* object) override
	{
		BPVariant* value = new BPVariant();
		ClassType* ClassObj = dynamic_cast<ClassType*>(object);
		value->SetValue<MemberType>(ClassObj->*Member);
		return value;
	}

	virtual void SetValue(BPSmartPtr<BPVariant> value, BPObject* object) override
	{
		ClassType* ClassObj = dynamic_cast<ClassType*>(object);
		ClassObj->*Member = value->GetValue<MemberType>();
	}

	MemberPointer Member;
};

#endif

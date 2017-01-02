#pragma once
#ifndef __BP_PROPERTY_H__
#define __BP_PROPERTY_H__
#include "Reflection/BPAny.h"

class BPObject;

class AbstractProperty
{
private:
	AbstractProperty* Next;
	friend class BPClass;

public:
	virtual ~AbstractProperty() {}

	std::string PropertyName;
	std::string PropertyDescription;
	unsigned int PropertyFlags;

	AbstractProperty(std::string name, std::string description, unsigned int flags)
	{
		PropertyName = name;
		PropertyDescription = description;
		PropertyFlags = flags;
	}

	AbstractProperty* GetNext() const { return Next; }

	virtual BPSmartPtr<BPAny> GetValue(BPObject* object) = 0;
	virtual void SetValue(BPSmartPtr<BPAny> value, BPObject* object) = 0;
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
	}

	virtual BPSmartPtr<BPAny> GetValue(BPObject* object) override
	{
		ClassType* ClassObj = dynamic_cast<ClassType*>(object);

		BPAny* value = new BPAny(ClassObj->*Member);
		return value;
	}

	virtual void SetValue(BPSmartPtr<BPAny> value, BPObject* object) override
	{
		ClassType* ClassObj = dynamic_cast<ClassType*>(object);
		ClassObj->*Member = value->GetValue<MemberType>();
	}

	MemberPointer Member;
};

#endif

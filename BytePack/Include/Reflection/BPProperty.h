#pragma once

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

	virtual void GetValue(ClassType* object) = 0;
	virtual void SetValue(ClassType* object) = 0;
};

template<class ClassType, class MemberType>
class MemberProperty : public ObjectProperty<ClassType>
{
public:

	typedef MemberType ClassType::* MemberPointer;
	MemberProperty(MemberPointer member, std::string name, std::string description, unsigned int flags)
		: ObjectProperty(name, description, flags)
		, Member(member)
	{

	}

	virtual void GetValue(ClassType* object) override
	{
		object->*Member;
	}

	virtual void SetValue(ClassType* object) override
	{
		object->*Member;
	}

	MemberPointer Member;
};
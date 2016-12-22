#pragma once
#include "BPProperty.h"
#include <vector>

template<class T>
class BPClassBuilder
{
public:
	BPClassBuilder(BPClass* classObject)
		: ClassObject(classObject)
	{

	}

	template<class MemberType>
	BPClassBuilder<T>& Property(MemberType T::* member, std::string name, std::string description, unsigned int flags)
	{
		Properties.push_back(new MemberProperty<T, MemberType>(member, name, description, flags));
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

	std::vector<ObjectProperty<T>*> Properties;
};


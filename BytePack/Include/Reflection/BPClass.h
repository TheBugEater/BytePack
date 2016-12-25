#pragma once
#ifndef __BP_CLASS_H__
#define __BP_CLASS_H__

#include "Reflection/BPClassFactory.h"
#include "Reflection/BPProperty.h"
#include "Reflection/BPSmartPtr.h"

enum PropertyFlags
{
	Writable = (0 << 0),
	Readable = (0 << 1),
	ReadWrite = (Writable + Readable)
};

#include <map>
#include <vector>

#define BP_REFLECT(CLASS) \
public:\
static class BPClass* StaticClass; \
virtual class BPClass* GetClass() { return CLASS::StaticClass; }

#define BP_BEGIN_CLASS_ROOT(CLASS) \
BP_BEGIN_IMPL_CLASS(CLASS, NULL)

#define BP_BEGIN_CLASS(CLASS, BASE) \
BP_BEGIN_IMPL_CLASS(CLASS, BASE::StaticClass)

#define BP_BEGIN_IMPL_CLASS(CLASS, BASEOBJ) \
class CLASS##Class : public BPClass \
{ \
public: \
	CLASS##Class() : BPClass(BASEOBJ, #CLASS) \
	{ \
		BuildProperties(); \
	} \
	virtual BPSmartPtr<class BPObject> CreateInstance() { return new CLASS(); } \
private: \
	void BuildProperties() \
	{ \
		BPClassBuilder<CLASS>(this) 

#define BP_END_CLASS(CLASS) ;\
	} \
}; \
CLASS##Class __##CLASS##ClassObj; \
BPClass* CLASS::StaticClass = &__##CLASS##ClassObj;

class BPClass
{
	typedef std::map<size_t, class AbstractProperty*> TypeProperties;

public:
	BPClass(BPClass* base, std::string name)
		: SuperClass(base)
		, ClassName(name)
	{
		BPClassFactory::Instance()->RegisterClass(this);
	}

	virtual BPSmartPtr<class BPObject> CreateInstance() { return nullptr; } \

	inline std::string& GetClassName() { return ClassName; }
	inline BPClass* GetBaseClass() { return SuperClass; }
	inline TypeProperties& GetProperties() { return Properties; }

	template<class ClassType>
	void SetPropertyValue(ClassType* obj, BPSmartPtr<BPVariant>& value, std::string name);

	template<class ClassType>
	BPSmartPtr<BPVariant>& GetPropertyValue(ClassType* obj, std::string name);

	template<class ClassType>
	void AddProperty(ObjectProperty<ClassType>* property);

private:

	std::string ClassName;

	BPClass* SuperClass;

	friend class BPClassFactory;
	BPClass* NextClass;

	TypeProperties Properties;
};

template<class ClassType>
void BPClass::AddProperty(ObjectProperty<ClassType>* property)
{
	Properties[std::hash<std::string>{}(property->PropertyName)] = property;
}

template<class ClassType>
void BPClass::SetPropertyValue(ClassType* obj, BPSmartPtr<BPVariant>& value, std::string name)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	ObjectProperty<ClassType>* ClassObj = dynamic_cast<ObjectProperty<ClassType>*>(Property);
	ClassObj->SetValue(value, obj);
}

template<class ClassType>
BPSmartPtr<BPVariant>& BPClass::GetPropertyValue(ClassType* obj, std::string name)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	ObjectProperty<ClassType>* ClassObj = dynamic_cast<ObjectProperty<ClassType>*>(Property);
	return ClassObj->GetValue(obj);
}

template<class T>
class BPClassBuilder
{
public:
	BPClassBuilder(BPClass* classObject)
		: ClassObject(classObject)
	{

	}

	template<class MemberType>
	BPClassBuilder<T>& Property(MemberType T::* member, std::string name, std::string description = "", unsigned int flags = 2)
	{
		Properties.push_back(new MemberProperty<T, MemberType>(member, name, description, flags));
		return *this;
	}

	template<class MemberType>
	BPClassBuilder<T>& Property(MemberType T::* member, std::string name, unsigned int flags)
	{
		Properties.push_back(new MemberProperty<T, MemberType>(member, name, "", flags));
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


#endif

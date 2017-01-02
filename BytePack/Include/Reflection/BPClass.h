#pragma once
#ifndef __BP_CLASS_H__
#define __BP_CLASS_H__

#include "Reflection/BPClassFactory.h"
#include "Reflection/BPProperty.h"
#include "Reflection/BPSmartPtr.h"

#include <map>
#include <vector>

enum EPropertyFlags 
{
	Writable = (0 << 0),
	Readable = (0 << 1),
	ReadWrite = (Writable | Readable)
};

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
		, PropertyHead(nullptr)
	{
		BPClassFactory::Instance()->RegisterClass(this);
	}

	virtual ~BPClass();

	virtual BPSmartPtr<class BPObject> CreateInstance() { return nullptr; } 

	inline std::string& GetClassName() { return ClassName; }
	inline BPClass* GetBaseClass() { return SuperClass; }
	inline TypeProperties& GetProperties() { return Properties; }

	template<class ClassType>
	void SetPropertyValue(ClassType* obj, BPSmartPtr<BPAny> value, std::string name);

	template<class ClassType>
	BPSmartPtr<BPAny> GetPropertyValue(ClassType* obj, std::string name);

	void AddProperty(AbstractProperty* property);

private:

	std::string ClassName;

	BPClass* SuperClass;

	friend class BPClassFactory;
	BPClass* NextClass;

	TypeProperties Properties;

	AbstractProperty* PropertyHead;
};

template<class ClassType> void BPClass::SetPropertyValue(ClassType* obj, BPSmartPtr<BPAny> value, std::string name)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	ClassObj->SetValue(value, obj);
}

template<class ClassType>
BPSmartPtr<BPAny> BPClass::GetPropertyValue(ClassType* obj, std::string name)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	return Property->GetValue(obj);
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
		return Property(member, name, "", flags);
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

	std::vector<AbstractProperty*> Properties;
};


#endif

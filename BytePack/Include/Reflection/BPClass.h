#pragma once
#ifndef __BP_CLASS_H__
#define __BP_CLASS_H__

#include "Reflection/BPClassFactory.h"
#include "Reflection/BPAny.h"
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
	virtual class BPObject* CreateInstance() { return new CLASS(); } \
private: \
	void BuildProperties() \
	{ \
		BPClassBuilder<CLASS>(this) 

#define BP_END_CLASS(CLASS) ;\
	} \
}; \
CLASS##Class __##CLASS##ClassObj; \
BPClass* CLASS::StaticClass = &__##CLASS##ClassObj; 

template<typename T, typename U> 
static constexpr size_t OffsetOf(U T::*member)
{
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

class BPClass
{
	typedef std::map<size_t, class BPProperty*> TypeProperties;

public:
	BPClass(BPClass* base, std::string name)
		: SuperClass(base)
		, ClassName(name)
		, PropertyHead(nullptr)
	{
		ClassID = BPClassFactory::Instance()->RegisterClass(this);
	}

	virtual	~BPClass();

	virtual class BPObject* CreateInstance() { return nullptr; } 

	inline unsigned int& GetClassID() { return ClassID; }
	inline std::string& GetClassName() { return ClassName; }
	inline BPClass* GetBaseClass() { return SuperClass; }
	inline TypeProperties& GetProperties() { return Properties; }

	template<class ClassType>
	void SetPropertyValue(std::string name, ClassType* obj, BPSmartPtr<BPAny> value);

	template<class ClassType>
	BPSmartPtr<BPAny> GetPropertyValue(ClassType* obj, std::string name);

	void AddProperty(BPProperty* property);

	void Serialize(class IBPStream* stream, class BPObject* Object);
	void Deserialize(class IBPStream* stream, class BPObject* Object);

private:

	std::string ClassName;
	unsigned int ClassID;

	BPClass* SuperClass;

	friend class BPClassFactory;
	BPClass* NextClass;

	TypeProperties Properties;

	BPProperty* PropertyHead;
};

template<class ClassType> void BPClass::SetPropertyValue(std::string name, ClassType* obj,  BPSmartPtr<BPAny> value)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	PropertySetValue(Property, obj, value);
}

template<class ClassType>
BPSmartPtr<BPAny> BPClass::GetPropertyValue(ClassType* obj, std::string name)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	return PropertyGetValue(Property, obj);
}

#endif

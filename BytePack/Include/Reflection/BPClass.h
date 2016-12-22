#pragma once

#include <map>
#include "Reflection/BPClassFactory.h"
#include "Reflection/BPProperty.h"
#include "Reflection/BPClassBuilder.h"
 
enum PropertyFlag
{
	Writable = (0 << 0),
	Readable = (0 << 1),
	ReadWrite = (Writable + Readable)
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
	BPSmartPtr<CLASS> CreateInstance() { return new CLASS(); } \
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

	inline std::string& GetClassName() { return ClassName; }
	inline BPClass* GetBaseClass() { return SuperClass; }
	inline TypeProperties& GetProperties() { return Properties; }

	template<class ClassType>
	void SetPropertyValue(ClassType* obj, std::string name);

	template<class ClassType>
	void GetPropertyValue(ClassType* obj, std::string name);

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
void BPClass::SetPropertyValue(ClassType* obj, std::string name)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	ObjectProperty<ClassType>* ClassObj = dynamic_cast<ObjectProperty<ClassType>*>(Property);
	ClassObj->SetValue(obj);
}

template<class ClassType>
void BPClass::GetPropertyValue(ClassType* obj, std::string name)
{
	auto Property = Properties[std::hash<std::string>{}(name)];
	ObjectProperty<ClassType>* ClassObj = dynamic_cast<ObjectProperty<ClassType>*>(Property);
	ClassObj->GetValue(obj);
}

#pragma once

#include <map>
#include "Reflection/BPClassFactory.h"
#include "Reflection/BPProperty.h"
#include "Reflection/BPClassBuilder.h"

#define BP_REFLECT(CLASS) \
public:\
static class BPClass* StaticClass; \
virtual class BPClass* GetClass() { return CLASS::StaticClass; }

#define BP_BEGIN_CLASS_ROOT(CLASS, FLAGS) \
BP_BEGIN_IMPL_CLASS(CLASS, NULL, FLAGS)

#define BP_BEGIN_CLASS(CLASS, BASE, FLAGS) \
BP_BEGIN_IMPL_CLASS(CLASS, BASE::StaticClass, FLAGS)

#define BP_BEGIN_IMPL_CLASS(CLASS, BASEOBJ, FLAGS) \
class CLASS##Class : public BPClass \
{ \
public: \
	CLASS##Class() : BPClass(BASEOBJ, #CLASS, FLAGS) \
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
	BPClass(BPClass* base, std::string name, unsigned int flags )
		: SuperClass(base)
		, ClassName(name)
		, ClassFlags(flags)
	{
		BPClassFactory::Instance()->RegisterClass(this);
	}

	inline std::string& GetClassName() { return ClassName; }
	inline unsigned int GetClassFlags() { return ClassFlags; }
	inline BPClass* GetBaseClass() { return SuperClass; }
	inline TypeProperties& GetProperties() { return Properties; }

	template<class ClassType>
	void AddProperty(ObjectProperty<ClassType>* property);

private:

	std::string ClassName;
	unsigned int ClassFlags;

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

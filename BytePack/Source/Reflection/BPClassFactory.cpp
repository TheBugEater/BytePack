#include "Reflection/BPClassFactory.h"
#include "Reflection/BPClass.h"

BPClassFactory* BPClassFactory::StaticInstance = nullptr;

BPClassFactory::BPClassFactory()
	: CurrentClassID(0)
{
}

BPClassFactory::~BPClassFactory()
{
}

BPClassFactory* BPClassFactory::Instance()
{
	if (!StaticInstance)
		StaticInstance = new BPClassFactory();

	return StaticInstance;
}

unsigned int BPClassFactory::RegisterClass(BPClass* Class)
{
	Class->NextClass = ReflectedClasses;
	ReflectedClasses = Class;
	return ++CurrentClassID;
}

BPClass* BPClassFactory::GetNextClass(BPClass* Class)
{
	if (!Class)
		return ReflectedClasses;

	return Class->NextClass;
}

BPClass* BPClassFactory::FindClassByName(std::string className)
{
	auto Class = ReflectedClasses;
	while (Class)
	{
		if (Class->GetClassName() == className)
			return Class;

		Class = Class->NextClass;
	}

	return nullptr;
}

BPClass* BPClassFactory::FindClassByID(unsigned int ID)
{
	auto Class = ReflectedClasses;
	while (Class)
	{
		if (Class->GetClassID() == ID)
			return Class;

		Class = Class->NextClass;
	}

	return nullptr;
}

BPObject* BPClassFactory::CreateClassInstanceByName(std::string name)
{
	auto Class = ReflectedClasses;
	while (Class)
	{
		if (Class->GetClassName() == name)
			return Class->CreateInstance();

		Class = Class->NextClass;
	}

	return nullptr;

}

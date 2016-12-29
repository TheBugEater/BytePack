#include "Reflection/BPClassFactory.h"
#include "Reflection/BPClass.h"

BPClassFactory* BPClassFactory::StaticInstance = nullptr;

BPClassFactory::BPClassFactory()
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

void BPClassFactory::RegisterClass(BPClass* Class)
{
	Class->NextClass = ReflectedClasses;
	ReflectedClasses = Class;
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

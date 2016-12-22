#pragma once
#ifndef __BP_CLASS_FACTORY_H__
#define __BP_CLASS_FACTORY_H__

#include <string>

class BPClassFactory
{
	BPClassFactory();

public:

	static BPClassFactory* Instance();

	void RegisterClass(class BPClass* Class);

	BPClass* GetClasses() const { return ReflectedClasses; }
	BPClass* GetNextClass(BPClass* Class);

	BPClass* FindClassByName(std::string name);

private:
	class BPClass* ReflectedClasses;

	static BPClassFactory* StaticInstance;
};

#endif

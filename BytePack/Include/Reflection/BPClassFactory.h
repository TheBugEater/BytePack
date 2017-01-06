#pragma once
#ifndef __BP_CLASS_FACTORY_H__
#define __BP_CLASS_FACTORY_H__

#include <string>
#include "BPSmartPtr.h"

class BPClassFactory
{
	BPClassFactory();

public:

	~BPClassFactory();

	static BPClassFactory* Instance();

	unsigned int RegisterClass(class BPClass* Class);

	BPClass* GetClasses() const { return ReflectedClasses; }
	BPClass* GetNextClass(BPClass* Class);

	BPClass* FindClassByName(std::string name);
	BPClass* FindClassByID(unsigned int ID);

	class BPObject* CreateClassInstanceByName(std::string name);

private:
	class BPClass* ReflectedClasses;

	static BPClassFactory* StaticInstance;
	
	unsigned int CurrentClassID;
};

#endif

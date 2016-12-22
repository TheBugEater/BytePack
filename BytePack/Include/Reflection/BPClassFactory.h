#pragma once
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


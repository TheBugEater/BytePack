#include <conio.h>
#include <iostream>
#include "Reflection\BPObject.h"

class Test : public BPObject
{
	BP_REFLECT(Test)

	int ID;
};

BP_BEGIN_CLASS(Test, BPObject)
.Property(&Test::ID, "id", "An Integer for Saving the ID", Readable | Writable)
.Build()
BP_END_CLASS(Test)

class Test2 : public BPObject
{
	BP_REFLECT(Test2)

	char Character;
	std::string Name;
};

BP_BEGIN_CLASS(Test2, BPObject)
.Property(&Test2::Character, "character", "Char Example", Readable | Writable)
.Property(&Test2::Name, "name", "Reflecting a Name String", Readable)
.Build()
BP_END_CLASS(Test2)

int main()
{
	auto TestClass = BPClassFactory::Instance()->FindClassByName("Test");

	auto Classes = BPClassFactory::Instance()->GetClasses();
	while (Classes)
	{
		std::cout << Classes->GetClassName().c_str() << std::endl;
		auto it = Classes->GetProperties().begin();
		while(it != Classes->GetProperties().end())
		{
			std::cout << "----> Property : " << it->second->PropertyName.c_str() << " | \"" << it->second->PropertyDescription.c_str()<< "\"" << std::endl;
			++it;
		}
		std::cout << "____________________" << std::endl;
		Classes = BPClassFactory::Instance()->GetNextClass(Classes);
	}

	Test test;
	test.ID = 1003;

	//auto val = Test::StaticClass->GetPropertyValue(&test, "id");
	//std::cout << std::endl << val->GetValue<int>();
	_getch();
}
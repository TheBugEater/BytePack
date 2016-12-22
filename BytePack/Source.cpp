#include <conio.h>
#include <iostream>
#include "Reflection\BPObject.h"

class Test : public BPObject
{
	BP_REFLECT(Test)

		int id;
};

BP_BEGIN_CLASS(Test, BPObject)
.Property(&Test::id, "id", "An ID", Readable | Writable)
.Build()
BP_END_CLASS(Test)

class Test2
{
	BP_REFLECT(Test2)

	char val;
	std::string name;
};

BP_BEGIN_CLASS(Test2, BPObject, 0)
.Property(&Test2::val, "val", "Value", Readable | Writable)
.Property(&Test2::name, "name", "Name Property", Readable)
.Build()
BP_END_CLASS(Test2)

int main()
{
	Test test;
	test.id = 10;

	Test::StaticClass->SetPropertyValue(&test, "id");

	auto Classes = BPClassFactory::Instance()->GetClasses();
	while (Classes)
	{
		std::cout << Classes->GetClassName().c_str() << std::endl;
		auto it = Classes->GetProperties().begin();
		while(it != Classes->GetProperties().end())
		{
			std::cout << "  Property : " << it->second->PropertyName.c_str() << " | " << it->second->PropertyDescription.c_str()<<std::endl;
			++it;
		}
		Classes = BPClassFactory::Instance()->GetNextClass(Classes);
	}
	_getch();
}
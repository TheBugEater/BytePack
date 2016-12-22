#include <conio.h>
#include <iostream>
#include "Reflection\BPObject.h"

class Test : public BPObject
{
	BP_REFLECT(Test)

		int id;
};

BP_BEGIN_CLASS(Test, BPObject, 0)
.Property(&Test::id, "id", "An ID", 0)
.Build()
BP_END_CLASS(Test)

class Test2
{
	BP_REFLECT(Test2)

	char val;
	std::string name;
};

BP_BEGIN_CLASS(Test2, BPObject, 0)
.Property(&Test2::val, "val", "Value", 0)
.Property(&Test2::name, "name", "Name Property", 0)
.Build()
BP_END_CLASS(Test2)

int main()
{
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
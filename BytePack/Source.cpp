#ifdef _WIN32 && _DEBUG
#include "vld.h" 
#pragma comment(lib, "vld.lib")
#endif

#include <conio.h>
#include <iostream>
#include "Reflection\BPObject.h"
#include "Include\Serialization\BPBinaryStream.h"

class Test : public BPObject
{
	BP_REFLECT(Test)

	uint64 ID;
	float floatVal;
};

BP_BEGIN_CLASS(Test, BPObject)
.Property(&Test::ID, "id", "An Integer for Saving the ID", EPropertyFlags::ReadWrite)
.Property(&Test::floatVal, "floatVal", "A Float Value", EPropertyFlags::ReadWrite)
.Build()
BP_END_CLASS(Test)

class Test2 : public BPObject
{
	BP_REFLECT(Test2)

	char Character;
	std::string name;
	Test* test;
};

BP_BEGIN_CLASS(Test2, BPObject)
.Property(&Test2::Character, "character", "Char Example", EPropertyFlags::ReadWrite)
.Property(&Test2::test, "test", "Reflecting a Pointer Object", EPropertyFlags::ReadWrite)
.Property(&Test2::name, "name", "Reflecting a String Object", EPropertyFlags::ReadWrite)
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
			std::cout << "----> Property : " << it->second->GetName().c_str() << " | \"" << it->second->GetDescription().c_str()<< "\"" << std::endl;
			++it;
		}
		std::cout << "____________________" << std::endl;
		Classes = BPClassFactory::Instance()->GetNextClass(Classes);
	}

	Test test1;
	size_t offset = OffsetOf(&Test::ID);
	test1.ID = 30;
	test1.floatVal = 520.042f;
	Test2 test2;
	test2.Character = 'H';
	test2.name = "Dilhan Geeth";
	test2.test = &test1;

	Test::StaticClass->SetPropertyValue("id", &test1, new BPAny((uint64)43));

	BPSmartPtr<BPBinaryStream> Stream = new BPBinaryStream();
	Stream->Serialize(&test2);

	_getch();
}
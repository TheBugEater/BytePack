#ifdef _WIN32 && _DEBUG
#include "vld.h" 
#pragma comment(lib, "vld.lib")
#endif

#include <conio.h>
#include <iostream>
#include "Reflection/BPObject.h"
#include "Reflection/BPClassBuilder.h"
#include "Serialization/BPBinaryStream.h"

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

	Test test1;
	test1.ID = 30;
	test1.floatVal = 520.042f;
	Test2 test2;
	test2.Character = 'H';
	test2.name = "Dilhan Geeth";
	test2.test = &test1;

	Test::StaticClass->SetPropertyValue("id", &test1, new BPAny((uint64)43));

	BPSmartPtr<BPBinaryStream> Stream = new BPBinaryStream();
	Stream->Serialize(&test2);
	Stream->SaveToFile("Hello.bin");
	Stream->LoadFromFile("Hello.bin");
	Stream->Deserialize(&test2);

	_getch();
}
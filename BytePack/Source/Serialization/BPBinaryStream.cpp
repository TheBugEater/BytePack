#include "Serialization/BPBinaryStream.h"
#include "Reflection/BPObject.h"
#include <iostream>

BPBinaryStream::BPBinaryStream()
{
}


BPBinaryStream::~BPBinaryStream()
{
}

void BPBinaryStream::Serialize(class BPObject* object)
{
	BPClass* Class = object->GetClass();
	if (Class)
	{
		Class->Serialize(this, object);
	}
}

void BPBinaryStream::Deserialize(class BPObject* object)
{
	BPClass* Class = object->GetClass();
	if (Class)
	{
		Class->Deserialize(this, object);
	}
}

void BPBinaryStream::Serialize(int8& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(int16& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(int32& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(int64& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(uint8& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(uint16& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(uint32& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(uint64& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(char& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(bool& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(float& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(double& value)
{
	std::cout << value << std::endl;
}

void BPBinaryStream::Serialize(std::string& value)
{
	std::cout << value << std::endl;
}

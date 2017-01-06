#include "Serialization/BPBinaryStream.h"
#include "Reflection/BPObject.h"
#include <iostream>

BPBinaryStream::BPBinaryStream()
{
}

BPBinaryStream::~BPBinaryStream()
{
}

void BPBinaryStream::SaveToFile(std::string filePath)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filePath.c_str(), "wb+");
	if (fp)
	{
		fwrite((char*)Buffer.GetBuffer(), 1, Buffer.GetBufferSize(), fp);
	}
	fclose(fp);
}

bool BPBinaryStream::LoadFromFile(std::string filePath)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filePath.c_str(), "rb+");
	if (fp)
	{
		fseek(fp, 0L, SEEK_END);
		uint32 size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		char* buffer = new char[size];
		fread(buffer, 1, size, fp);
		Buffer.Reset();
		Buffer.InitBuffer(buffer, size);
		delete buffer;
		fclose(fp);
		return true;
	}
	return false;
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
	Buffer.Write((char*)&value, sizeof(int8));
}

void BPBinaryStream::Serialize(int16& value)
{
	Buffer.Write((char*)&value, sizeof(int16));
}

void BPBinaryStream::Serialize(int32& value)
{
	Buffer.Write((char*)&value, sizeof(int32));
}

void BPBinaryStream::Serialize(int64& value)
{
	Buffer.Write((char*)&value, sizeof(int64));
}

void BPBinaryStream::Serialize(uint8& value)
{
	Buffer.Write((char*)&value, sizeof(uint8));
}

void BPBinaryStream::Serialize(uint16& value)
{
	Buffer.Write((char*)&value, sizeof(uint16));
}

void BPBinaryStream::Serialize(uint32& value)
{
	Buffer.Write((char*)&value, sizeof(uint32));
}

void BPBinaryStream::Serialize(uint64& value)
{
	Buffer.Write((char*)&value, sizeof(uint64));
}

void BPBinaryStream::Serialize(char& value)
{
	Buffer.Write((char*)&value, sizeof(char));
}

void BPBinaryStream::Serialize(bool& value)
{
	Buffer.Write((char*)&value, sizeof(bool));
}

void BPBinaryStream::Serialize(float& value)
{
	Buffer.Write((char*)&value, sizeof(float));
}

void BPBinaryStream::Serialize(double& value)
{
	Buffer.Write((char*)&value, sizeof(double));
}

void BPBinaryStream::Serialize(std::string& value)
{
	uint32 stringSize = (uint32)value.size();
	Buffer.Write((char*)&stringSize, sizeof(uint32));

	Buffer.Write((char*)value.c_str(), stringSize);
}

void BPBinaryStream::Deserialize(int8& value)
{
	Buffer.Read((char*)&value, sizeof(int8));
}

void BPBinaryStream::Deserialize(int16& value)
{
	Buffer.Read((char*)&value, sizeof(int16));
}

void BPBinaryStream::Deserialize(int32& value)
{
	Buffer.Read((char*)&value, sizeof(int32));
}

void BPBinaryStream::Deserialize(int64& value)
{
	Buffer.Read((char*)&value, sizeof(int64));
}

void BPBinaryStream::Deserialize(uint8& value)
{
	Buffer.Read((char*)&value, sizeof(uint8));
}

void BPBinaryStream::Deserialize(uint16& value)
{
	Buffer.Read((char*)&value, sizeof(uint16));
}

void BPBinaryStream::Deserialize(uint32& value)
{
	Buffer.Read((char*)&value, sizeof(uint32));
}

void BPBinaryStream::Deserialize(uint64& value)
{
	Buffer.Read((char*)&value, sizeof(uint64));
}

void BPBinaryStream::Deserialize(char& value)
{
	Buffer.Read((char*)&value, sizeof(char));
}

void BPBinaryStream::Deserialize(bool& value)
{
	Buffer.Read((char*)&value, sizeof(bool));
}

void BPBinaryStream::Deserialize(float& value)
{
	Buffer.Read((char*)&value, sizeof(float));
}

void BPBinaryStream::Deserialize(double& value)
{
	Buffer.Read((char*)&value, sizeof(double));
}

void BPBinaryStream::Deserialize(std::string& value)
{
	uint32 stringSize;
	Buffer.Read((char*)&stringSize, sizeof(uint32));

	char* stringVal = new char[stringSize];
	Buffer.Read((char*)stringVal, stringSize);

	value = std::string(stringVal, stringSize);
	delete stringVal;
}


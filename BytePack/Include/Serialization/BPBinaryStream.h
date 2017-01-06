#pragma once
#ifndef __BP_BINARY_STREAM_H__
#define __BP_BINARY_STREAM_H__

#include "Serialization/IBPStream.h"
#include "Serialization/BPBuffer.h"

class BPBinaryStream : public IBPStream
{
public:
	BPBinaryStream();
	~BPBinaryStream();

	void SaveToFile(std::string filePath);
	bool LoadFromFile(std::string filePath);

	virtual void Serialize(int8& value);
	virtual void Serialize(int16& value);
	virtual void Serialize(int32& value);
	virtual void Serialize(int64& value);
	virtual void Serialize(uint8& value);
	virtual void Serialize(uint16& value);
	virtual void Serialize(uint32& value);
	virtual void Serialize(uint64& value);
	virtual void Serialize(char& value);
	virtual void Serialize(bool& value);
	virtual void Serialize(float& value);
	virtual void Serialize(double& value);
	virtual void Serialize(std::string& value);

	virtual void Deserialize(int8& value);
	virtual void Deserialize(int16& value);
	virtual void Deserialize(int32& value);
	virtual void Deserialize(int64& value);
	virtual void Deserialize(uint8& value);
	virtual void Deserialize(uint16& value);
	virtual void Deserialize(uint32& value);
	virtual void Deserialize(uint64& value);
	virtual void Deserialize(char& value);
	virtual void Deserialize(bool& value);
	virtual void Deserialize(float& value);
	virtual void Deserialize(double& value);
	virtual void Deserialize(std::string& value);

	virtual void Serialize(class BPObject* object);
	virtual void Deserialize(class BPObject* object);

private:
	BPBuffer Buffer;
};

#endif
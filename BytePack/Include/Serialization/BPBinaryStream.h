#pragma once
#ifndef __BP_BINARY_STREAM_H__
#define __BP_BINARY_STREAM_H__

#include "Serialization/IBPStream.h"

class BPBinaryStream : public IBPStream
{
public:
	BPBinaryStream();
	~BPBinaryStream();

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

	virtual void Serialize(class BPObject* object);
	virtual void Deserialize(class BPObject* object);
};

#endif
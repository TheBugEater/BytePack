#pragma once
#ifndef __IBP_STREAM_H__
#define __IBP_STREAM_H__

#include "Reflection/BPTypes.h"
#include "Reflection/BPSmartPtr.h"

class IBPStream : public BPSmartPtrObj
{
public:
	IBPStream();
	~IBPStream();

	virtual void Serialize(int8& value) = 0;
	virtual void Serialize(int16& value) = 0;
	virtual void Serialize(int32& value) = 0;
	virtual void Serialize(int64& value) = 0;
	virtual void Serialize(uint8& value) = 0;
	virtual void Serialize(uint16& value) = 0;
	virtual void Serialize(uint32& value) = 0;
	virtual void Serialize(uint64& value) = 0;
	virtual void Serialize(char& value) = 0;
	virtual void Serialize(bool& value) = 0;
	virtual void Serialize(float& value) = 0;
	virtual void Serialize(double& value) = 0;
	virtual void Serialize(std::string& value) = 0;

	virtual void Deserialize(int8& value) = 0;
	virtual void Deserialize(int16& value) = 0;
	virtual void Deserialize(int32& value) = 0;
	virtual void Deserialize(int64& value) = 0;
	virtual void Deserialize(uint8& value) = 0;
	virtual void Deserialize(uint16& value) = 0;
	virtual void Deserialize(uint32& value) = 0;
	virtual void Deserialize(uint64& value) = 0;
	virtual void Deserialize(char& value) = 0;
	virtual void Deserialize(bool& value) = 0;
	virtual void Deserialize(float& value) = 0;
	virtual void Deserialize(double& value) = 0;
	virtual void Deserialize(std::string& value) = 0;

	friend IBPStream& operator<<(IBPStream& stream, int8& value);
	friend IBPStream& operator<<(IBPStream& stream, int16& value);
	friend IBPStream& operator<<(IBPStream& stream, int32& value);
	friend IBPStream& operator<<(IBPStream& stream, int64& value);
	friend IBPStream& operator<<(IBPStream& stream, uint8& value);
	friend IBPStream& operator<<(IBPStream& stream, uint16& value);
	friend IBPStream& operator<<(IBPStream& stream, uint32& value);
	friend IBPStream& operator<<(IBPStream& stream, uint64& value);
	friend IBPStream& operator<<(IBPStream& stream, char& value);
	friend IBPStream& operator<<(IBPStream& stream, bool& value);
	friend IBPStream& operator<<(IBPStream& stream, float& value);
	friend IBPStream& operator<<(IBPStream& stream, double& value);
	friend IBPStream& operator<<(IBPStream& stream, std::string& value);
	friend IBPStream& operator<<(IBPStream& stream, class BPObject* value);

	friend IBPStream& operator>>(IBPStream& stream, int8& value);
	friend IBPStream& operator>>(IBPStream& stream, int16& value);
	friend IBPStream& operator>>(IBPStream& stream, int32& value);
	friend IBPStream& operator>>(IBPStream& stream, int64& value);
	friend IBPStream& operator>>(IBPStream& stream, uint8& value);
	friend IBPStream& operator>>(IBPStream& stream, uint16& value);
	friend IBPStream& operator>>(IBPStream& stream, uint32& value);
	friend IBPStream& operator>>(IBPStream& stream, uint64& value);
	friend IBPStream& operator>>(IBPStream& stream, char& value);
	friend IBPStream& operator>>(IBPStream& stream, bool& value);
	friend IBPStream& operator>>(IBPStream& stream, float& value);
	friend IBPStream& operator>>(IBPStream& stream, double& value);
	friend IBPStream& operator>>(IBPStream& stream, std::string& value);
	friend IBPStream& operator>>(IBPStream& stream, class BPObject* value);

	virtual void Serialize(class BPObject* object) = 0;
	virtual void Deserialize(class BPObject* object) = 0;
};

#endif

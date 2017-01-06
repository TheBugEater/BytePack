#pragma once
#ifndef __BP_BUFFER_H__
#define __BP_BUFFER_H__

#include "Reflection/BPTypes.h"

class BPBuffer
{
public:
	BPBuffer();
	~BPBuffer();
	
	void Write(char* value, size_t size);
	void Read(char* value, size_t size);

	void InitBuffer(char* buffer, size_t size);
	void Reset();

	uint8* GetBuffer() const;

	size_t GetBufferSize() const { return BufferSize; }

private:
	std::vector<uint8> Buffer;

	size_t CurrentOffset;
	size_t BufferSize;
};

#endif

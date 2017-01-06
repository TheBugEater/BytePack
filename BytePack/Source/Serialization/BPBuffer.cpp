#include "Serialization/BPBuffer.h"

BPBuffer::BPBuffer()
	: CurrentOffset(0)
{
	Buffer = std::vector<uint8>(16);
	BufferSize = 16;
}


BPBuffer::~BPBuffer()
{
}

void BPBuffer::InitBuffer(char* buffer, size_t size)
{
	Buffer.resize(size);
	BufferSize = size;
	CurrentOffset = 0;
	memcpy(&Buffer[0], buffer, size);
}

void BPBuffer::Reset()
{
	CurrentOffset = 0;
	Buffer.clear();
	Buffer.resize(16);
}

void BPBuffer::Write(char* value, size_t size)
{
	if (CurrentOffset + size >= BufferSize)
	{
		BufferSize += 16;
		Buffer.resize(BufferSize);
	}

	memcpy(&Buffer[CurrentOffset], value, size);
	CurrentOffset += size;
}

void BPBuffer::Read(char* value, size_t size)
{
	memcpy(value, &Buffer[CurrentOffset], size);
	CurrentOffset += size;
}

uint8* BPBuffer::GetBuffer() const
{
	return (uint8*)Buffer.data();
}

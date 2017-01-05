#include "Serialization/IBPStream.h"



IBPStream::IBPStream()
{
}


IBPStream::~IBPStream()
{
}

IBPStream& operator<<(IBPStream& stream, int8& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, int16& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, int32& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, int64& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, uint8& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, uint16& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, uint32& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, uint64& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, char& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, bool& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, float& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, double& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, std::string& value)
{
	stream.Serialize(value);
	return stream;
}

IBPStream& operator<<(IBPStream& stream, class BPObject* value)
{
	stream.Serialize(value);
	return stream;
}


#pragma once
#include "Reflection/BPSmartPtr.h"
#include "Reflection/BPTypes.h"
#include <string>
#include "Serialization/IBPStream.h"

class BPProperty : public BPSmartPtrObj
{
public:
	BPProperty(size_t memberOffset, std::string name, std::string description, unsigned int flags, ETypeNames type)
		: MemberOffset(memberOffset)
		, Name(name)
		, Description(description)
		, Flags(flags)
		, PropertyType(type)
	{

	}

	std::string GetName() const { return Name; }
	std::string GetDescription() const { return Description; }
	unsigned int GetFlags() const { return Flags; }
	ETypeNames GetPropertyType() const { return PropertyType; }

	BPSmartPtr<BPProperty> GetNext() const { return Next; }

	virtual void SerializeProperty(class IBPStream& stream, class BPObject* object)
	{

	}

	virtual void DeserializeProperty(class IBPStream& stream, class BPObject* object)
	{

	}

protected:
	size_t MemberOffset;
	
	std::string Name;
	std::string Description;
	unsigned int Flags;

	ETypeNames PropertyType;

private:
	class BPClass* OwnerClass;
	
	friend class BPClass;
	BPProperty* Next;
};

template<typename type>
class BPPropertyT : public BPProperty
{
public:

	BPPropertyT(size_t memberOffset, std::string name, std::string description, unsigned int flags)
		: BPProperty(memberOffset, name, description, flags, Type_NONE)
	{

	}

	type& GetValue(void* obj) 
	{ 
		return *(type*)((PTR_TO_UINT)obj + MemberOffset); 
	} 

	void SetValue(void* obj, const type& value) 
	{ 
		*(type*)((PTR_TO_UINT)obj + MemberOffset) = value;
	}

	virtual void SerializeProperty(class IBPStream& stream, class BPObject* object)
	{
		stream << GetValue(object);
	}

	virtual void DeserializeProperty(class IBPStream& stream, class BPObject* object)
	{

	}

};

#define DEFINE_NUMERIC_PROPERTY(type) \
template<>\
class BPPropertyT<type> : public BPProperty\
{\
public:\
\
	BPPropertyT(size_t memberOffset, std::string name, std::string description, unsigned int flags)\
		: BPProperty(memberOffset, name, description, flags, Type_##type)\
	{\
\
	}\
\
	type& GetValue(void* obj) \
	{ \
		return *(type*)((PTR_TO_UINT)obj + MemberOffset); \
	} \
\
	void SetValue(void* obj, const type& value) \
	{ \
		*(type*)((PTR_TO_UINT)obj + MemberOffset) = value;\
	}\
\
	virtual void SerializeProperty(class IBPStream& stream, class BPObject* object)\
	{\
		stream << (type)GetValue(object);\
	}\
\
	virtual void DeserializeProperty(class IBPStream& stream, class BPObject* object)\
	{\
\
	}\
\
};

DEFINE_NUMERIC_PROPERTY(char)
DEFINE_NUMERIC_PROPERTY(int8)
DEFINE_NUMERIC_PROPERTY(int16)
DEFINE_NUMERIC_PROPERTY(int32)
DEFINE_NUMERIC_PROPERTY(int64)
DEFINE_NUMERIC_PROPERTY(uint8)
DEFINE_NUMERIC_PROPERTY(uint16)
DEFINE_NUMERIC_PROPERTY(uint32)
DEFINE_NUMERIC_PROPERTY(uint64)
DEFINE_NUMERIC_PROPERTY(float)
DEFINE_NUMERIC_PROPERTY(double)
DEFINE_NUMERIC_PROPERTY(bool)

template<>
class BPPropertyT<std::string> : public BPProperty
{
public:
	BPPropertyT(size_t memberOffset, std::string name, std::string description, unsigned int flags)
		: BPProperty(memberOffset, name, description, flags, Type_string)
	{

	}

	std::string& GetValue(void* obj)
	{ 
		return *(std::string*)((PTR_TO_UINT)obj + MemberOffset); 
	} 

	void SetValue(void* obj, const std::string& value) 
	{ 
		*(std::string*)((PTR_TO_UINT)obj + MemberOffset) = value;
	}

	virtual void SerializeProperty(class IBPStream& stream, class BPObject* object)
	{
		stream << GetValue(object);
	}

	virtual void DeserializeProperty(class IBPStream& stream, class BPObject* object)
	{

	}
};

template<>
class BPPropertyT<BPObject*> : public BPProperty
{
public:
	BPPropertyT(size_t memberOffset, std::string name, std::string description, unsigned int flags)
		: BPProperty(memberOffset, name, description, flags, Type_object)
	{

	}

	BPObject* GetValue(void* obj)
	{ 
		return *(BPObject**)((PTR_TO_UINT)obj + MemberOffset); 
	} 

	void SetValue(void* obj, const BPObject* value) 
	{ 
		*(BPObject**)((PTR_TO_UINT)obj + MemberOffset) = (BPObject*)value;
	}

	virtual void SerializeProperty(class IBPStream& stream, class BPObject* object)
	{
		stream << GetValue(object);
	}

	virtual void DeserializeProperty(class IBPStream& stream, class BPObject* object)
	{

	}
};

static BPSmartPtr<BPAny> PropertyGetValue(BPProperty* property, void* obj)
{
	switch (property->GetPropertyType())
	{
	case Type_int8:
		return new BPAny(dynamic_cast<BPPropertyT<int8>*>(property)->GetValue(obj));
	case Type_int16:
		return new BPAny(dynamic_cast<BPPropertyT<int16>*>(property)->GetValue(obj));
	case Type_int32:
		return new BPAny(dynamic_cast<BPPropertyT<int32>*>(property)->GetValue(obj));
	case Type_int64:
		return new BPAny(dynamic_cast<BPPropertyT<int64>*>(property)->GetValue(obj));
	case Type_uint8:
		return new BPAny(dynamic_cast<BPPropertyT<uint8>*>(property)->GetValue(obj));
	case Type_uint16:
		return new BPAny(dynamic_cast<BPPropertyT<uint16>*>(property)->GetValue(obj));
	case Type_uint32:
		return new BPAny(dynamic_cast<BPPropertyT<uint32>*>(property)->GetValue(obj));
	case Type_uint64:
		return new BPAny(dynamic_cast<BPPropertyT<uint64>*>(property)->GetValue(obj));
	case Type_bool:
		return new BPAny(dynamic_cast<BPPropertyT<bool>*>(property)->GetValue(obj));
	case Type_float:
		return new BPAny(dynamic_cast<BPPropertyT<float>*>(property)->GetValue(obj));
	case Type_char:
		return new BPAny(dynamic_cast<BPPropertyT<char>*>(property)->GetValue(obj));
	case Type_double:
		return new BPAny(dynamic_cast<BPPropertyT<double>*>(property)->GetValue(obj));
	case Type_object:
		return new BPAny(dynamic_cast<BPPropertyT<BPObject*>*>(property)->GetValue(obj));
	case Type_string:
		return new BPAny(dynamic_cast<BPPropertyT<std::string>*>(property)->GetValue(obj));
	case Type_NONE:
	default:
		return new BPAny();
		break;
	}
}

static void PropertySetValue(BPProperty* property, void* obj, BPSmartPtr<BPAny> value)
{
	switch (property->GetPropertyType())
	{
	case Type_int8:
		dynamic_cast<BPPropertyT<int8>*>(property)->SetValue(obj, value->GetValue<int8>());
		break;
	case Type_int16:
		dynamic_cast<BPPropertyT<int16>*>(property)->SetValue(obj, value->GetValue<int16>());
		break;
	case Type_int32:
		dynamic_cast<BPPropertyT<int32>*>(property)->SetValue(obj, value->GetValue<int32>());
		break;
	case Type_int64:
		dynamic_cast<BPPropertyT<int64>*>(property)->SetValue(obj, value->GetValue<int64>());
		break;
	case Type_uint8:
		dynamic_cast<BPPropertyT<uint8>*>(property)->SetValue(obj, value->GetValue<uint8>());
		break;
	case Type_uint16:
		dynamic_cast<BPPropertyT<uint16>*>(property)->SetValue(obj, value->GetValue<uint16>());
		break;
	case Type_uint32:
		dynamic_cast<BPPropertyT<uint32>*>(property)->SetValue(obj, value->GetValue<uint32>());
		break;
	case Type_uint64:
		dynamic_cast<BPPropertyT<uint64>*>(property)->SetValue(obj, value->GetValue<uint64>());
		break;
	case Type_bool:
		dynamic_cast<BPPropertyT<bool>*>(property)->SetValue(obj, value->GetValue<bool>());
		break;
	case Type_float:
		dynamic_cast<BPPropertyT<float>*>(property)->SetValue(obj, value->GetValue<float>());
		break;
	case Type_char:
		dynamic_cast<BPPropertyT<char>*>(property)->SetValue(obj, value->GetValue<char>());
		break;
	case Type_double:
		dynamic_cast<BPPropertyT<double>*>(property)->SetValue(obj, value->GetValue<double>());
		break;
	case Type_object:
		dynamic_cast<BPPropertyT<BPObject*>*>(property)->SetValue(obj, value->GetValue<BPObject*>());
		break;
	case Type_string:
		dynamic_cast<BPPropertyT<std::string>*>(property)->SetValue(obj, value->GetValue<std::string>());
		break;
	case Type_NONE:
	default:
		break;
	}
}


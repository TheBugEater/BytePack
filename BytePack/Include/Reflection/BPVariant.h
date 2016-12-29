#pragma once
#ifndef __BP_VARIANT_H__
#define __BP_VARIANT_H__

#include "Reflection/BPAny.h"
#include <type_traits>
#include <string>
#include <assert.h>
#include <vector>

class BPObject;

template<typename Type>
static ValueTypes ToValueType()
{
	if (typeid(char).hash_code() == typeid(Type).hash_code())
	{
		return ValueTypes::TypeChar;
	}
	else if (typeid(bool).hash_code() == typeid(Type).hash_code())
	{
		return ValueTypes::TypeBool;
	}
	else if (typeid(int).hash_code() == typeid(Type).hash_code())
	{
		return ValueTypes::TypeInt;
	}
	else if (typeid(float).hash_code() == typeid(Type).hash_code())
	{
		return ValueTypes::TypeFloat;
	}
	else if (typeid(double).hash_code() == typeid(Type).hash_code())
	{
		return ValueTypes::TypeDouble;
	}
	else if (typeid(long).hash_code() == typeid(Type).hash_code())
	{
		return ValueTypes::TypeLong;
	}
	else if (typeid(std::string).hash_code() == typeid(Type).hash_code())
	{
		return ValueTypes::TypeString;
	}
	else
	{
		return ValueTypes::TypeObject;
	}
}

template <size_t arg1, size_t ... others>
struct TypeMax;

template <size_t arg>
struct TypeMax<arg>
{
	static const size_t value = arg;
};

template <size_t arg1, size_t arg2, size_t ... others>
struct TypeMax<arg1, arg2, others...>
{
	static const size_t value = arg1 >= arg2 ? TypeMax<arg1, others...>::value :
		TypeMax<arg2, others...>::value;
};

template<typename... args>
struct TypeMaxSize
{
	static const size_t size = TypeMax<sizeof(args)...>::value;
};

template<typename... args>
struct TypeMaxAlign
{
	static const size_t size = TypeMax<alignof(args)...>::value;
};

using TypeSize = TypeMaxSize<bool, signed char, unsigned char, char, wchar_t, short int, unsigned short int, int, unsigned int,
	long int, unsigned long int, long long int, unsigned long long int, float, double, void*>;

using TypeAlign = TypeMaxAlign<bool, signed char, unsigned char, char, wchar_t, short int, unsigned short int, int, unsigned int,
	long int, unsigned long int, long long int, unsigned long long int, float, double, void*>;

class BPVariant : public BPSmartPtrObj
{
public:

	typedef std::aligned_storage <TypeSize::size,TypeAlign::size>::type StorageData;

	ValueTypes GetType() const { return ValueType; }

	StorageData Data;
	size_t TypeID;

	template<typename Type>
	void SetValue(Type value)
	{
		new (&Data) Type(value);
		TypeID = typeid(Type).hash_code();
		ValueType = ToValueType<Type>();
	}

	template<typename Type>
	Type GetValue()
	{
		assert(TypeID == typeid(Type).hash_code());

		return *reinterpret_cast<Type*>(&Data);
	}

	template<>
	BPObject* GetValue<BPObject*>()
	{
		unsigned int* PtrAddr = reinterpret_cast<unsigned int*>(&Data);
		BPObject* Obj = (BPObject*)(*PtrAddr);
		return Obj;
	}

private:
	ValueTypes ValueType;
};

#endif


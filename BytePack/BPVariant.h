#pragma once
#include "Reflection/BPSmartPtr.h"
#include <type_traits>
#include <string>
#include <assert.h>

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

	StorageData Data;
	size_t TypeID;

	template<typename Type>
	void SetValue(Type value)
	{
		new (&Data) Type(value);
		TypeID = typeid(Type).hash_code();
	}

	template<typename Type>
	Type GetValue()
	{
		assert(TypeID == typeid(Type).hash_code());

		return *reinterpret_cast<Type*>(&Data);
	}
};


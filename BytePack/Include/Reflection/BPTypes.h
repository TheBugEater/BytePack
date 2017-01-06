#pragma once
#ifndef __BP_TYPES_H__
#define __BP_TYPES_H__
#include <string>
#include <vector>

// Unsigned base types.
typedef unsigned char 		uint8;		// 8-bit  unsigned.
typedef unsigned short int	uint16;		// 16-bit unsigned.
typedef unsigned int		uint32;		// 32-bit unsigned.
typedef unsigned long long	uint64;		// 64-bit unsigned.

										// Signed base types.
typedef	signed char			int8;		// 8-bit  signed.
typedef signed short int	int16;		// 16-bit signed.
typedef signed int	 		int32;		// 32-bit signed.
typedef signed long long	int64;		// 64-bit signed.

										// Character types.
typedef char				ANSICHAR;	// An ANSI character       
typedef wchar_t				WIDECHAR;	// A wide character        
typedef uint8				CHAR8;		// An 8-bit character type 
typedef uint16				CHAR16;		// A 16-bit character type 
typedef uint32				CHAR32;		// A 32-bit character type 
typedef WIDECHAR			TCHAR;		// A switchable character  

#ifdef _WIN64
#define PTR_TO_UINT uint64
#elif _WIN32
#define PTR_TO_UINT uint32
#endif

#define DEFINE_TYPE(num, type) Type_##type = num,

enum ETypeNames
{
	DEFINE_TYPE(0, NONE)
	DEFINE_TYPE(1, uint8)
	DEFINE_TYPE(2, uint16)
	DEFINE_TYPE(3, uint32)
	DEFINE_TYPE(4, uint64)
	DEFINE_TYPE(5, int8)
	DEFINE_TYPE(6, int16)
	DEFINE_TYPE(7, int32)
	DEFINE_TYPE(8, int64)
	DEFINE_TYPE(9, float)
	DEFINE_TYPE(10, double)
	DEFINE_TYPE(11, bool)
	DEFINE_TYPE(12, char)
	DEFINE_TYPE(13, object)
	DEFINE_TYPE(14, string)
};

#define TYPE_NAME_TEST_RETURN(type, type_hash) \
if(typeid(type).hash_code() == type_hash) \
{\
	return ETypeNames::Type_##type; \
}

static ETypeNames ToValueType(size_t type_hash)
{
	TYPE_NAME_TEST_RETURN(uint8, type_hash)
	TYPE_NAME_TEST_RETURN(uint16, type_hash)
	TYPE_NAME_TEST_RETURN(uint32, type_hash)
	TYPE_NAME_TEST_RETURN(uint64, type_hash)
	TYPE_NAME_TEST_RETURN(int8, type_hash)
	TYPE_NAME_TEST_RETURN(int16, type_hash)
	TYPE_NAME_TEST_RETURN(int32, type_hash)
	TYPE_NAME_TEST_RETURN(int64, type_hash)
	TYPE_NAME_TEST_RETURN(float, type_hash)
	TYPE_NAME_TEST_RETURN(double, type_hash)
	TYPE_NAME_TEST_RETURN(bool, type_hash)
	TYPE_NAME_TEST_RETURN(char, type_hash)

	if(typeid(class BPObject*).hash_code() == type_hash) 
	{
		return ETypeNames::Type_object;
	}

	if(typeid(std::string).hash_code() == type_hash) 
	{
		return ETypeNames::Type_string;
	}

	return ETypeNames::Type_NONE;
}

#endif // !__BP_TYPES_H__


#pragma once
#ifndef __BP_ANY_H__
#define __BP_ANY_H__

#include "Reflection/BPSmartPtr.h"

class BPObject;

enum class ValueTypes
{
	TypeChar,
	TypeBool,
	TypeInt,
	TypeFloat,
	TypeDouble,
	TypeLong,
	TypeString,
	TypeObject
};

static ValueTypes ToValueType(size_t type_hash)
{
	if (typeid(char).hash_code() == type_hash)
	{
		return ValueTypes::TypeChar;
	}
	else if (typeid(bool).hash_code() == type_hash)
	{
		return ValueTypes::TypeBool;
	}
	else if (typeid(int).hash_code() == type_hash)
	{
		return ValueTypes::TypeInt;
	}
	else if (typeid(float).hash_code() == type_hash)
	{
		return ValueTypes::TypeFloat;
	}
	else if (typeid(double).hash_code() == type_hash)
	{
		return ValueTypes::TypeDouble;
	}
	else if (typeid(long).hash_code() == type_hash)
	{
		return ValueTypes::TypeLong;
	}
	else if (typeid(std::string).hash_code() == type_hash)
	{
		return ValueTypes::TypeString;
	}
	else
	{
		return ValueTypes::TypeObject;
	}
}

#define SAFE_DELETE_PTR(x) { if(x) { delete x; x = nullptr; } }

class BPAny : public BPSmartPtrObj
{
public:
	BPAny()
		: Content(nullptr)
	{

	}

	BPAny(const BPAny& value)
		: Content(value.Content ? value.Content->Clone() : nullptr)
	{

	}

	template<typename T>
	BPAny(const T& value)
	{
		Content = new Holder<T>(value);
	}

	~BPAny()
	{
		SAFE_DELETE_PTR(Content);
	}

	BPAny& operator=(const BPAny& value)
	{
		this->Content = value.Content;
		return *this;
	}

	BPAny& operator=(const BPAny&& value)
	{
		this->Content = value.Content;
		return *this;
	}

	template<typename T>
	BPAny& operator=(const T& value)
	{
		SAFE_DELETE_PTR(Content);
		Content = new Holder<T>(value);
	}

	template<typename T>
	void SetValue(const T& value)
	{
		SAFE_DELETE_PTR(Content);
		Content = new Holder<T>(value);
	}

	template<typename T>
	T GetValue()
	{
		auto HolderVal = dynamic_cast<Holder<T>*>(Content);
		return HolderVal->HolderContent;
	}

	ValueTypes GetType()
	{
		return ToValueType(Content->GetTypeInfo().hash_code());
	}

	/*************************************************
	-------------- Holder Definitions ----------------
	**************************************************
	**************************************************/
private:

	class PlaceHolder
	{
	public:
		virtual ~PlaceHolder() { }

		virtual const type_info& GetTypeInfo() = 0;

		virtual PlaceHolder* Clone() = 0;
	};

	template<typename T>
	class Holder : public PlaceHolder
	{
	public:

		Holder(const T& value)
			: HolderContent(value)
		{
		}
		
		virtual const type_info& GetTypeInfo()
		{
			return typeid(T);
		}

		virtual PlaceHolder* Clone()
		{
			return new Holder<T>(HolderContent);
		}

		T HolderContent;
	};

	PlaceHolder* Content;
};

#endif //__BP_ANY_H__

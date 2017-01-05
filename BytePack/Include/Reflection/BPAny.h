#pragma once
#ifndef __BP_ANY_H__
#define __BP_ANY_H__

#include "Reflection/BPSmartPtr.h"
#include "Reflection/BPTypes.h"

class BPObject;

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
		SAFE_DELETE_PTR(Content);
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

	ETypeNames GetType()
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

#pragma once
#define SAFE_AddRef(x) if(x) { ((BPSmartPtrObj*)x)->AddRef(); }
#define SAFE_ReleaseRef(x) if(x) { ((BPSmartPtrObj*)x)->ReleaseRef(); }

class BPSmartPtrObj
{
public:
	BPSmartPtrObj(void) : RefCount(0) {}
	virtual ~BPSmartPtrObj() {} 

	void AddRef(void)
	{
		RefCount++;
	}

	void ReleaseRef(void)
	{
		if (--RefCount <= 0) { delete this; }
	}

public:
	unsigned int RefCount;
};

template<class T>
class BPSmartPtr
{
public:
	BPSmartPtr(void) : Reference(nullptr) { }

	// Copy Constructors
	BPSmartPtr(const BPSmartPtr<T>& copy)
	{
		this->Reference = copy.Reference;
		SAFE_AddRef(this->Reference);
	}

	BPSmartPtr(T* copy)
	{
		this->Reference = copy;
		SAFE_AddRef(this->Reference);
	}

	template<typename T2>
	BPSmartPtr(const BPSmartPtr<T2>& copy)
	{
		this->Reference = copy.Reference;
		SAFE_AddRef(this->Reference);
	}

	// Destructor
	~BPSmartPtr(void)
	{
		SAFE_ReleaseRef(this->Reference);
	}
	
	inline BPSmartPtr<T>& operator=(T* ref);
	inline BPSmartPtr<T>& operator=(const BPSmartPtr<T>& ref);

	inline T* operator->();
	inline const T* operator->() const;
	inline T& operator*();

private:
	T* Reference;
};


template<class T> BPSmartPtr<T>& BPSmartPtr<T>::operator=(T* ref)
{
	this->Reference = ref;
	SAFE_AddRef(this->Reference);
}

template<class T> BPSmartPtr<T>& BPSmartPtr<T>::operator=(const BPSmartPtr<T>& ref)
{
	this->Reference = ref.Reference;
	SAFE_AddRef(this->Reference);
}

template<class T> T* BPSmartPtr<T>::operator->()
{
	return this->Reference;
}

template<class T> const T* BPSmartPtr<T>::operator->() const
{
	return this->Reference;
}

template<class T> T& BPSmartPtr<T>::operator*()
{
	return *this->Reference;
}

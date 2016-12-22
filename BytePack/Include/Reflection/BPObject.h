#pragma once
#include "Reflection\BPClass.h"
#include "Reflection\BPSmartPtr.h"

class BPObject : public BPSmartPtrObj
{
	BP_REFLECT(BPObject)

	std::string GetClassName() { return GetClass()->GetClassName(); }
};


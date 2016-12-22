#pragma once
#include "Reflection\BPClass.h"

class BPObject : public BPSmartPtrObj
{
	BP_REFLECT(BPObject)

	std::string GetClassName() { return GetClass()->GetClassName(); }
};


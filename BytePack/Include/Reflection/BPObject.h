#pragma once
#ifndef __BP_OBJECT_H__
#define __BP_OBJECT_H__

#include "Reflection/BPClass.h"

class BPObject : public BPSmartPtrObj
{
	BP_REFLECT(BPObject)

	std::string GetClassName() { return GetClass()->GetClassName(); }
};

#endif

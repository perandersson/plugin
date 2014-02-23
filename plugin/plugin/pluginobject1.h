#pragma once
#include "defines.h"

//
// Base class for everything exposed using the plugin framework
struct PLUGIN_API IPluginObject1
{
public:
	virtual ~IPluginObject1() {}

	//
	// Increments the internal reference counter for this object.
	//
	// @return The new reference count.
	virtual PL_UINT64 AddRef() = 0;

	//
	// Decrements the internal reference counter for this object. The owner plugin is
	// free to release this objects internal memory whenever it reaches 0 - if it want's to.
	//
	// @reutrn The new reference count
	virtual PL_UINT64 Release() = 0;

	//
	// Convert this type into a new type - if possible. This is up the the one exposing
	// the original pointer to begin with
	//
	// @param type
	//			The new type
	// @param _out_Ptr
	//			A memory location where we put the new pointer
	// @return PL_RESOK if successfull; PL_RESERR otherwise;
	virtual PL_RES ConvertToType(PL_TYPE type, void** _out_Ptr) = 0;
};

DEFINE_PLTYPE(IPluginObject1, 1);

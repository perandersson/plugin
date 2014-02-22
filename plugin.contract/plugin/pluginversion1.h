#pragma once
#ifndef _IPLUGIN_VERSION1_H_
#define _IPLUGIN_VERSION1_H_

#include "pluginobject1.h"

//
//
DEFINE_INTERFACE(IPluginVersion1, IPluginObject1)
{
	//
	// @return The major component of this version instance
	virtual int GetMajor() const = 0;

	//
	// @return The minor component of this version instance
	virtual int GetMinor() const = 0;

	//
	// @return The patch component of this version instance
	virtual int GetPatch() const = 0;
};

#endif

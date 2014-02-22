#pragma once
#ifndef _IPLUGIN_SERVICE_REFERENCES1_H_
#define _IPLUGIN_SERVICE_REFERENCES1_H_

#include "pluginobject1.h"

DECLARE_INTERFACE(IPluginServiceReference1);

//
//
DEFINE_INTERFACE(IPluginServiceReferences1, IPluginObject1)
{
	//
	//
	virtual void OnServiceReference(IPluginServiceReference1* reference) = 0;
};

#endif


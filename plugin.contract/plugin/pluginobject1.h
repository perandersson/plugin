#pragma once
#ifndef _IPLUGIN_OBJECT_H_
#define _IPLUGIN_OBJECT_H_

#include "defines.h"

struct PLUGIN_API IPluginContext1;
struct PLUGIN_API IPlugin1;
struct PLUGIN_API IPluginActivator1;
struct PLUGIN_API IPluginVersion1;
struct PLUGIN_API IPluginService1;
struct PLUGIN_API IPluginServiceReference1;
struct PLUGIN_API IPluginServiceReferences1;
struct PLUGIN_API IPluginServiceListener1;
struct PLUGIN_API IPluginListener1;

//
// Base class for everything exposed using the plugin framework
struct PLUGIN_API IPluginObject1
{
public:
	virtual ~IPluginObject1() {}
};


#endif

#pragma once
#ifndef _PLUGIN_CONTRACT_H_
#define _PLUGIN_CONTRACT_H_

//
// This is the version 1 of the plugin library
//

#include "pluginactivator1.h"
#include "plugin1.h"
#include "plugincontext1.h"
#include "pluginlistener1.h"
#include "pluginservice1.h"
#include "pluginservicelistener1.h"
#include "pluginservicereference1.h"
#include "pluginservicereferences1.h"
#include "pluginversion1.h"

//
// Typedefs for prettier interface
//

typedef IPluginActivator1 IPluginActivator;
typedef IPlugin1 IPlugin;
typedef IPluginListener1 IPluginListener;
typedef IPluginContext1 IPluginContext;
typedef IPluginService1 IPluginService;
typedef IPluginServiceListener1 IPluginServiceListener;
typedef IPluginServiceReference1 IPluginServiceReference;
typedef IPluginServiceReferences1 IPluginServiceReferences;
typedef IPluginVersion1 IPluginVersion;
typedef GetPluginActivator1Func GetPluginActivatorFunc;

#endif

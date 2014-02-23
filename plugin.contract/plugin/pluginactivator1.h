#pragma once
#ifndef _IPLUGIN_ACTIVATOR1_H_
#define _IPLUGIN_ACTIVATOR1_H_

#include "pluginobject1.h"

//
// Interface that represents the entry- and exit point of a plugin.
DECLARE_INTERFACE(IPluginActivator1, IPluginObject1)
{
	//
	// Starts this plugin instance and registers it's internal resources
	//
	// @param context
	//			The plugin context. It manages all the active plugin- and plugin features.
	// @param plugin
	//			The plugin representation inside the engine
	virtual void Start(IPluginContext1* context, IPlugin1* plugin) = 0;

	//
	// Stop this plugin instance and release it's internal resources.
	//
	// @param plugin
	//			The plugin representation inside the engine
	virtual void Stop(IPlugin1* plugin) = 0;
};

// 
// Function signature for the function used to return the actual plugin activator
typedef IPluginActivator1* (*GetPluginActivator1Func)(void);

//
// Function signature for retrieving the plugin version
typedef const char* (*GetPluginVersionFunc)(void);

#ifndef DEFINE_PLUGIN
#define DEFINE_PLUGIN(Type, Version) \
	extern "C" { \
	Type __pluginActivator; \
	PLUGIN_API IPluginActivator* __cdecl GetPluginActivator1() { \
		return &__pluginActivator; \
	} \
	PLUGIN_API const char* __cdecl GetPluginVersion() { \
	\
		return Version; \
	}\
}
#endif

#endif

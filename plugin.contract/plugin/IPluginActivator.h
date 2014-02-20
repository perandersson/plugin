#pragma once
#ifndef _PLUGIN_IPLUGIN_ACTIVATOR_H_
#define _PLUGIN_IPLUGIN_ACTIVATOR_H_

#include "defines.h"
#include <memory>

namespace plugin
{
	namespace contract
	{
		class PLUGIN_API IPluginContext;
		class PLUGIN_API IPlugin;

		//
		// Interface that represents the entry- and exit point of a plugin.
		class PLUGIN_API IPluginActivator
		{
		public:
			virtual ~IPluginActivator() {}

			//
			// Starts this plugin instance and registers it's internal resources
			//
			// @param context
			//			The plugin context. It manages all the active plugin- and plugin features.
			// @param plugin
			//			The plugin representation inside the engine
			virtual void Start(IPluginContext* context, IPlugin* plugin) = 0;

			//
			// Stop this plugin instance and release it's internal resources.
			//
			// @param plugin
			//			The plugin representation inside the engine
			virtual void Stop(IPlugin* plugin) = 0;
		};

		// 
		// Function signature for the function used to return the actual plugin activator
		typedef IPluginActivator*(*GetPluginActivatorFunc)();

		//
		// Function signature for retrieving the expected engine major version
		typedef int(*GetPluginEngineMajorVersionFunc)(void);

		//
		// Function signature for retrieving the expected engine minor version
		typedef int(*GetPluginEngineMinorVersionFunc)(void);

		//
		// Function signature for retriving the plugin version
		typedef const char* (*GetPluginVersionFunc)(void);
	}
}

#ifndef DEFINE_PLUGIN
#define DEFINE_PLUGIN(Type, Version) \
	extern "C" { \
	PLUGIN_API plugin::contract::IPluginActivator* GetPluginActivator() { \
		return new Type(); \
	} \
	\
	PLUGIN_API int GetPluginEngineMajorVersion() { \
		return PLUGIN_ENGINE_MAJOR_VERSION; \
	} \
	PLUGIN_API int GetPluginEngineMinorVersion() { \
		return PLUGIN_ENGINE_MINOR_VERSION; \
	} \
	PLUGIN_API const char* GetPluginVersion() { \
		return Version; \
	} \
}
#endif

#endif

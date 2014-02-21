#pragma once
#ifndef _CORE_PLUGIN_CONTEXT_H_
#define _CORE_PLUGIN_CONTEXT_H_

#include <plugin/contract.h>
#include "ModuleLoader.h"
#include <memory>
#include <list>

namespace plugin
{
	using namespace contract;

	namespace core
	{
		class Plugin;
		class Version;
		class ServiceReference;

		//
		// Base class for the plugin manager.
		class PluginContext : public IPluginContext
		{
			typedef std::list<std::shared_ptr<Plugin>> Plugins;

		protected:
			PluginContext();

		public:
			virtual ~PluginContext();

			//
			// Load the supplied plugin file
			//
			// @param fileName
			// @param name
			void LoadPlugin(const char* fileName, const std::string& name);

			//
			// Start a new plugin using the supplied activator
			//
			// @param library
			//			The library
			// @param activator
			//			The plugin activator class responsible for starting- and stopping the plugin
			// @param name
			//			The name of the plugin
			// @param version
			//			The plugin version
			void StartPlugin(LibraryHandle library, IPluginActivator* activator, const std::string& name, const Version& version);

			//
			// Notifies all the listeners
			//
			// @param type
			//			The service type
			// @param service
			//			The actual service
			// @param status
			//			The status of the service
			void NotifyServiceChanged(ServiceReference* reference, IServiceListener::Status status);

			//
			// Notifies all the listeners
			//
			// @param plugin
			//			The plugin that's being changed
			// @param status
			//			The status of the plugin
			void NotifyPluginChanged(Plugin* plugin, IPluginListener::Status status);

		// IPluginContext
		public:
			virtual IServiceReference* GetServiceReference(const type_info& type);
			virtual void GetServiceReferences(const type_info& type, IServiceReferences* callback);

		private:
			Plugins mPlugins;
		};
	}
}

#endif


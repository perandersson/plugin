#pragma once
#ifndef _CORE_PLUGIN_CONTEXT_H_
#define _CORE_PLUGIN_CONTEXT_H_

#include <plugin/contract.h>
#include "moduleloader.h"
#include <memory>
#include <list>

namespace plugin
{
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
			typedef std::list<Plugin*> UnregisterPluginsList;

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
			// Unload the supplied plugin file
			//
			// @param fileName
			void UnloadPlugin(const char* fileName);

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
			void NotifyServiceChanged(ServiceReference* reference, IPluginServiceListener::Status status);

			//
			// Notifies all the listeners
			//
			// @param plugin
			//			The plugin that's being changed
			// @param status
			//			The status of the plugin
			void NotifyPluginChanged(Plugin* plugin, IPluginBundleListener::Status status);

		// IPluginContext
		public:
			virtual IPluginServiceReference* GetServiceReference(const type_info& type);
			virtual IPluginServiceReference* GetServiceReference(const type_info& type, const char* filter);
			virtual void GetServiceReferences(const type_info& type, IPluginServiceReferences* callback);
			virtual void GetServiceReferences(const type_info& type, const char* filter, IPluginServiceReferences* callback);

		private:
			Plugins mPlugins;
			UnregisterPluginsList mUnregistrationList;
		};
	}
}

#endif


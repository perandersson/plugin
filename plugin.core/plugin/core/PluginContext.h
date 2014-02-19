#pragma once
#ifndef _CORE_PLUGIN_CONTEXT_H_
#define _CORE_PLUGIN_CONTEXT_H_

#include <plugin/contract.h>
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
		// 
		class PluginContext : public IPluginContext
		{
			typedef std::list<std::shared_ptr<Plugin>> Plugins;

		protected:
			PluginContext();

		public:
			virtual ~PluginContext();

			//
			// Start a new plugin using the supplied activator
			//
			// @param activator
			//			The plugin activator class responsible for starting- and stopping the plugin
			// @param version
			//			The plugin version
			void StartPlugin(IPluginActivator* activator, const Version& version);

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

		// IPluginContext
		public:
			virtual IServiceReference* GetServiceReference(const type_info& type);
			virtual IService* GetService(IServiceReference* reference);
			virtual void UngetService(IServiceReference* reference);

		private:
			Plugins mPlugins;
		};
	}
}

#endif


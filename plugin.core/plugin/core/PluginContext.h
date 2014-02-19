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

		// IPluginContext
		public:
			virtual void RegisterService(const type_info& type, IService* service);
			virtual IServiceReference* GetServiceReference(const type_info& type);
			virtual IService* GetService(IServiceReference* reference);
			virtual void UngetService(IServiceReference* reference);
			virtual void AddServiceListener(IServiceListener* listener);
			virtual void RemoveServiceListener(IServiceListener* listener);

		private:
			Plugins mPlugins;
			std::shared_ptr<Plugin> mCurrentPlugin;
		};
	}
}

#endif


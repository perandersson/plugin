#pragma once
#ifndef _CORE_PLUGIN_CONTEXT_H_
#define _CORE_PLUGIN_CONTEXT_H_

#include <plugin/contract.h>
#include <memory>
#include <list>

namespace plugin
{
	namespace core
	{
		class Plugin;

		class PluginContext : public IPluginContext
		{
			typedef std::list<std::shared_ptr<Plugin>> Plugins;

		public:
			PluginContext();
			virtual ~PluginContext();

			//
			// Start a new plugin
			//
			// @param activator
			// @param version string
			void StartPlugin(IPluginActivator* activator, int majorVersion, int minorVersion, int patchVersion);

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


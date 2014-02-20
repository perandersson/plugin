#pragma once
#ifndef _CORE_PLUGIN_H_
#define _CORE_PLUGIN_H_

#include <plugin/contract.h>
#include <list>
#include <memory>
#include "Version.h"
#include "ModuleLoader.h"

#ifdef __GNUC__
#include <ext/hash_map>
namespace std { using namespace __gnu_cxx; }
#else
#include <hash_map>
#endif

namespace plugin
{
	using namespace contract;

	namespace core
	{
		class ServiceReference;
		class PluginContext;

		//
		// Implementation of the IPlugin contract
		class Plugin : public IPlugin
		{
			typedef std::hash_map<std::string, std::shared_ptr<ServiceReference>> ServiceReferences;
			typedef std::list<IServiceListener*> ServiceListeners;
			typedef std::list<IPluginListener*> PluginListeners;

		public:
			Plugin(LibraryHandle library, IPluginActivator* activator, const std::string& name, const Version& version);
			~Plugin();

			//
			// Starts this plugin in the supplied context
			//
			// @param context
			//			The context where all the plugins resides
			void Start(PluginContext* context);

			//
			// Stops this plugin from running.
			void Stop();

			//
			// Locates a service reference using the supplied type
			//
			// @param type
			//			The type
			// @return A service reference
			ServiceReference* FindServiceReference(const type_info& type);

			//
			// Notifies all the listeners connected via this plugin
			//
			// @param service
			//			The actual service
			// @param status
			//			The status of the service
			void NotifyServiceChanged(ServiceReference* reference, IServiceListener::Status status);

			//
			// Notifies all the listeners connected via this plugin
			//
			// @param plugin
			//			The plugin that's being changed
			// @param status
			//			The status of the plugin
			void NotifyPluginChanged(Plugin* plugin, IPluginListener::Status status);

		// IPlugin
		public:
			virtual IServiceReference* RegisterService(const type_info& type, IService* service);
			virtual void UnregisterServices(const type_info& type);
			virtual void UnregisterService(IServiceReference* reference);
			virtual void AddServiceListener(IServiceListener* listener);
			virtual void RemoveServiceListener(IServiceListener* listener);
			virtual void AddPluginListener(IPluginListener* listener);
			virtual void RemovePluginListener(IPluginListener* listener);
			virtual Status GetStatus() const;
			virtual const IVersion* GetVersion() const;
			virtual IPluginContext* GetPluginContext();
			virtual const char* GetName();

		private:
			LibraryHandle mLibrary;
			PluginContext* mPluginContext;
			IPluginActivator* mActivator;
			Version mVersion;
			ServiceReferences mReferences;
			ServiceListeners mServiceListeners;
			PluginListeners mPluginListeners;
			Status mStatus;
			std::string mName;
		};
	}
}

#endif

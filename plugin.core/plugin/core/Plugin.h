#pragma once
#ifndef _CORE_PLUGIN_H_
#define _CORE_PLUGIN_H_

#include <plugin/contract.h>
#include <list>
#include <memory>
#include "Version.h"

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

		public:
			Plugin(PluginContext& context, IPluginActivator* activator, const Version& version);
			~Plugin();

			//
			// Starts this plugin in the supplied context
			//
			// @param context
			//			The context where all the plugins resides
			void Start(PluginContext& context);

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
			// @param context
			//			The responsible plugin context running all the plugins
			// @param type
			//			The service type
			// @param service
			//			The actual service
			void NotifyServiceListeners(PluginContext& context, const type_info& type, ServiceReference& reference);

		// IPlugin
		public:
			virtual void RegisterService(const type_info& type, IService* service);
			virtual void AddServiceListener(IServiceListener* listener);
			virtual void RemoveServiceListener(IServiceListener* listener);
			virtual Status GetStatus() const;
			virtual const IVersion& GetVersion() const;

		private:
			PluginContext& mPluginContext;
			std::auto_ptr<IPluginActivator> mActivator;
			Version mVersion;
			ServiceReferences mReferences;
			ServiceListeners mListeners;
			Status mStatus;
		};
	}
}

#endif

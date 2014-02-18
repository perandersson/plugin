#pragma once
#ifndef _CORE_PLUGIN_H_
#define _CORE_PLUGIN_H_

#include <plugin/contract.h>
#include <list>
#include <memory>

#ifdef __GNUC__
#include <ext/hash_map>
namespace std { using namespace __gnu_cxx; }
#else
#include <hash_map>
#endif

namespace plugin
{
	namespace core
	{
		class ServiceReference;
		class PluginContext;

		class Plugin : public IPlugin
		{
			typedef std::hash_map<std::string, std::shared_ptr<ServiceReference>> ServiceReferences;
			typedef std::list<IServiceListener*> ServiceListeners;

		public:
			Plugin();
			Plugin(std::auto_ptr<IPluginActivator> activator);
			~Plugin();

			//
			// @return TRUE if this plugin is valid; FALSE otherwise
			bool IsValid() const;

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
			// @param type
			// @param service
			// @return
			ServiceReference* RegisterService(const type_info& type, IService* service);

			//
			// @param type
			// @param plugin
			// @param service
			void NotifyServiceListeners(const type_info& type, PluginContext* context, ServiceReference* reference);

			//
			// @param listener
			void AddServiceListener(IServiceListener* listener);

		public:
			static Plugin INVALID_PLUGIN;
			
		private:
			std::auto_ptr<IPluginActivator> mActivator;
			ServiceReferences mReferences;
			ServiceListeners mListeners;
		};
	}
}

#endif

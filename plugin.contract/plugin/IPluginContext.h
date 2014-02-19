#pragma once
#ifndef _PLUGIN_IPLUGIN_CONTEXT_H_
#define _PLUGIN_IPLUGIN_CONTEXT_H_

#include "defines.h"
#include <typeinfo>

namespace plugin
{
	namespace contract
	{
		class PLUGIN_API IService;
		class PLUGIN_API IServiceReference;
		class PLUGIN_API IServiceListener;

		//
		//
		class PLUGIN_API IPluginContext
		{
		public:
			virtual ~IPluginContext() {}

		public:
			//
			// Register a new plugin service. Services are only allowed to be registered during a plugins ACTIVATION phase and it's the plugin
			// that owns the actual memory of the service. This means that the plugin is responsible to clean the memory up during the DEACTIVATION phase.
			//
			// @param type
			//			The type of the supplied service
			// @param service
			//			The service we want to register.
			virtual void RegisterService(const type_info& type, IService* service) = 0;

			//
			// Retrieves a specific service reference based on it's type
			//
			// @param type
			//			The service type
			// @return A reference created by the plugin engine if found; NULL otherwise
			virtual IServiceReference* GetServiceReference(const type_info& type) = 0;

			//
			// Resolves a service based on it's service reference. This ensures that the actual pointer
			// to the service is never deleted as long as it's in use
			//
			// @param reference
			//			The service reference
			// @return
			virtual IService* GetService(IServiceReference* reference) = 0;

			//
			// Releases the service object based on it's service reference
			//
			// @param reference
			//			The service reference
			virtual void UngetService(IServiceReference* reference) = 0;

			//
			// Add a service listener. This listener will receive events when services are registered and unregistered.
			// Listener instances are bound to a specific plugin. This means that they are automatically removed during the plugin's DEACTIVATION phase 
			//
			// @remark You are only allowed to register a component listener during the ACTIVATION phase of a plugin.
			// @param listener
			//			The listener instance
			virtual void AddServiceListener(IServiceListener* listener) = 0;

			//
			// Remove a service listener
			//
			// @param listener
			virtual void RemoveServiceListener(IServiceListener* listener) = 0;
		};
	}
}

#endif

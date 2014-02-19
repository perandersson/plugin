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
		class PLUGIN_API IServiceReferences;

		//
		//
		class PLUGIN_API IPluginContext
		{
		public:
			virtual ~IPluginContext() {}

		public:
			//
			// Retrieves a specific service reference based on it's type. If multiple services has registered the same type
			// then return the first one that's registered.
			//
			// @param type
			//			The service type
			// @return A reference created by the plugin engine if found; NULL otherwise
			virtual IServiceReference* GetServiceReference(const type_info& type) = 0;

			//
			// Retrieves a all service reference implementing the supplied type. 
			//
			// @param type
			//			The service type
			// @param callback
			//			A callack instance
			virtual void GetServiceReferences(const type_info& type, IServiceReferences* callback) = 0;

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
		};
	}
}

#endif

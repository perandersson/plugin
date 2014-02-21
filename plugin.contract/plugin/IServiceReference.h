#pragma once
#ifndef _PLUGIN_ISERVICE_REFERENCE_H_
#define _PLUGIN_ISERVICE_REFERENCE_H_

#include "defines.h"

namespace plugin
{
	namespace contract
	{
		class PLUGIN_API IPlugin;

		//
		// Interface that symbolizes a placeholder for a registered service.
		class PLUGIN_API IServiceReference
		{
		public:
			virtual ~IServiceReference() {}

		public:
			//
			// @return The plugin this service reference is connected to
			virtual IPlugin* GetPlugin() = 0;

			//
			// @return The plugin this service reference is connected to
			virtual const IPlugin* GetPlugin() const = 0;

			//
			// @return The type that the service reference is implementing
			virtual const type_info& GetType() const = 0;

			//
			// Resolves the service based on this reference. This ensures that the actual pointer
			// to the service is never deleted as long as it's in use.
			//
			// @return A pointer to the actual service; NULL if the service is no longer in memory
			virtual IService* GetService() = 0;

			//
			// Releases the service object based on it's service reference
			virtual void Release() = 0;
		};
	}
}

#endif

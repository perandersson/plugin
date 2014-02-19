#pragma once
#ifndef _PLUGIN_ISERVICE_LISTENER_H_
#define _PLUGIN_ISERVICE_LISTENER_H_

#include "defines.h"
#include <typeinfo>

namespace plugin
{
	namespace contract
	{
		class PLUGIN_API IServiceReference;
		class PLUGIN_API IPluginContext;

		//
		//
		class PLUGIN_API IServiceListener
		{
		public:
			virtual ~IServiceListener() {}

		public:
			//
			// Notifies that a service has been registered
			//
			// @param context
			// @param type
			// @param reference
			virtual void ServiceRegistered(IPluginContext& context, const type_info& type, IServiceReference& reference) = 0;

			//
			// Notifies that a service has been unregistered
			//
			// @remark This method is invoked right before the service's internal memory is released
			//
			// @param context
			// @param type
			// @param reference
			virtual void ServiceUnregisted(IPluginContext& context,  const type_info& type, const IServiceReference& reference) = 0;
		};
	}
}

#endif

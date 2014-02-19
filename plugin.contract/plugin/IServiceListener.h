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
			enum PLUGIN_API Status {
				//
				// Status if a service is registered
				STATUS_REGISTERED,

				//
				// Status if a service is unregistered
				STATUS_UNREGISTERED
			};

		public:
			virtual ~IServiceListener() {}

		public:
			//
			// Notifies that the status a service has been changed
			//
			// @param reference
			// @param status
			virtual void OnServiceChanged(IServiceReference& reference, Status status) = 0;
		};
	}
}

#endif

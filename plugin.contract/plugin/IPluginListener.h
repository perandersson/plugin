#pragma once
#ifndef _PLUGIN_LISTENER_H_
#define _PLUGIN_LISTENER_H_

#include "defines.h"

namespace plugin
{
	namespace contract
	{
		class PLUGIN_API IPlugin;

		//
		// 
		class PLUGIN_API IPluginListener
		{
		public:
			enum PLUGIN_API Status {
				//
				// The plugin is activated.
				STATUS_ACTIVE,

				//
				// The plugin has been inactivated
				STATUS_INACTIVE,
			};

		public:
			virtual ~IPluginListener() {}

		public:
			//
			// Method called when the status of the supplied plugin has been changed
			//
			// @param plugin
			//			The plugin that's being changed
			// @param status
			//			What happened with the plugin
			virtual void OnPluginChanged(IPlugin* plugin, Status status) = 0;
		};
	}
}

#endif

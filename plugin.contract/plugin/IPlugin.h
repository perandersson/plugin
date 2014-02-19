#pragma once
#ifndef _PLUGIN_IPLUGIN_H_
#define _PLUGIN_IPLUGIN_H_

#include "defines.h"

namespace plugin
{
	namespace contract
	{
		class PLUGIN_API IVersion;

		//
		// Interface representing the actual plugin. 
		class PLUGIN_API IPlugin
		{
		public:
			enum Status {
				//
				// Symbolizes that the plugin is starting up.
				STATUS_STARTING,

				//
				// Symbolizes that the plugin is active and all it's services registered inside
				// the plugin engine
				STATUS_ACTIVE,

				//
				// An inactive status means that the plugin engine is aware of the plugin but none of
				// the services are registrered.
				STATUS_INACTIVE
			};

		public:
			virtual ~IPlugin() {}

		public:
			//
			// @return The status for this plugin
			virtual Status GetStatus() const = 0;

			//
			// @return The version of this plugin.
			virtual const IVersion& GetVersion() const = 0;
		};
	}
}

#endif
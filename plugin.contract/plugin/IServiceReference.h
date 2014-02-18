#pragma once
#ifndef _PLUGIN_ISERVICE_REFERENCE_H_
#define _PLUGIN_ISERVICE_REFERENCE_H_

#include "defines.h"

namespace plugin
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
	};
}

#endif

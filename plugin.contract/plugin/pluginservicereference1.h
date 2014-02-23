#pragma once
#ifndef _IPLUGIN_SERVICE_REFERENCE1_H_
#define _IPLUGIN_SERVICE_REFERENCE1_H_

#include "pluginobject1.h"

//
// Interface that symbolizes a placeholder for a registered service.
DECLARE_INTERFACE(IPluginServiceReference1, IPluginObject1)
{
	//
	// @return The plugin this service reference is connected to
	virtual IPlugin1* GetPlugin() = 0;

	//
	// @return The plugin this service reference is connected to
	virtual const IPlugin1* GetPlugin() const = 0;

	//
	// @return The type that the service reference is implementing
	virtual const type_info& GetType() const = 0;

	//
	// Resolves the service based on this reference. This ensures that the actual pointer
	// to the service is never deleted as long as it's in use. This increases the internal reference counter for
	// the service.
	//
	// @return A pointer to the actual service; NULL if the service is no longer in memory
	virtual IPluginService1* GetService() = 0;

	//
	// Decreases the reference counter Releases the service object.
	virtual void Release() = 0;
};

#endif


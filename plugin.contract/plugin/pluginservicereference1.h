#pragma once
#ifndef _IPLUGIN_SERVICE_REFERENCE1_H_
#define _IPLUGIN_SERVICE_REFERENCE1_H_

#include "defines.h"

DECLARE_INTERFACE(IPluginBundle1);
DECLARE_INTERFACE(IPluginService1);

//
// Interface that symbolizes a placeholder for a registered service.
DEFINE_INTERFACE(IPluginServiceReference1, IPluginObject)
{
	//
	// @return The plugin this service reference is connected to
	virtual IPluginBundle1* GetPlugin() = 0;

	//
	// @return The plugin this service reference is connected to
	virtual const IPluginBundle1* GetPlugin() const = 0;

	//
	// @return The type that the service reference is implementing
	virtual const type_info& GetType() const = 0;

	//
	// Resolves the service based on this reference. This ensures that the actual pointer
	// to the service is never deleted as long as it's in use.
	//
	// @return A pointer to the actual service; NULL if the service is no longer in memory
	virtual IPluginService1* GetService() = 0;

	//
	// Releases the service object based on it's service reference
	virtual void Release() = 0;
};

#endif


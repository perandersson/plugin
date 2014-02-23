#pragma once
#ifndef _IPLUGIN_SERVICE_LISTENER1_H_
#define _IPLUGIN_SERVICE_LISTENER1_H_

#include "pluginobject1.h"

//
//
DECLARE_INTERFACE(IPluginServiceListener1, IPluginObject1)
{
	enum PLUGIN_API Status {
		//
		// Status if a service is registered
		STATUS_REGISTERED = 0,

		//
		// Status if a service is unregistered
		STATUS_UNREGISTERED = 1
	};

	//
	// Notifies that the status a service has been changed
	//
	// @param reference
	// @param status
	virtual void OnServiceChanged(IPluginServiceReference1* reference, Status status) = 0;
};

#endif

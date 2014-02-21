#pragma once
#ifndef _IPLUGIN_SERVICE_LISTENER1_H_
#define _IPLUGIN_SERVICE_LISTENER1_H_

#include "defines.h"

DECLARE_INTERFACE(IPluginServiceReference1);
DECLARE_INTERFACE(IPluginContext1);

//
//
DEFINE_INTERFACE(IPluginServiceListener1, IPluginObject)
{
	enum PLUGIN_API Status {
		//
		// Status if a service is registered
		STATUS_REGISTERED = 1,

		//
		// Status if a service is unregistered
		STATUS_UNREGISTERED = 2
	};

	//
	// Notifies that the status a service has been changed
	//
	// @param reference
	// @param status
	virtual void OnServiceChanged(IPluginServiceReference1* reference, Status status) = 0;
};

#endif

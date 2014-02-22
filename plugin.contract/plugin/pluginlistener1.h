#pragma once
#ifndef _IPLUGIN_LISTENER1_H_
#define _IPLUGIN_LISTENER1_H_

#include "defines.h"

DECLARE_INTERFACE(IPlugin1);

//
// 
DEFINE_INTERFACE(IPluginListener1, IPluginObject)
{
	enum PLUGIN_API Status {
		//
		// The plugin is activated.
		STATUS_ACTIVE = 1,

		//
		// The plugin has been inactivated
		STATUS_INACTIVE = 2,
	};

	//
	// Method called when the status of the supplied plugin has been changed
	//
	// @param plugin
	//			The plugin that's being changed
	// @param status
	//			What happened with the plugin
	virtual void OnPluginChanged(IPlugin1* plugin, Status status) = 0;
};

#endif

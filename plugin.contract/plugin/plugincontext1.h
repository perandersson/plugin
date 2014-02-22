#pragma once
#ifndef _IPLUGIN_CONTEXT1_H_
#define _IPLUGIN_CONTEXT1_H_

#include "pluginobject1.h"

DECLARE_INTERFACE(IPluginServiceReference1);
DECLARE_INTERFACE(IPluginServiceReferences1);

//
//
DEFINE_INTERFACE(IPluginContext1, IPluginObject1)
{
	//
	// Retrieves a specific service reference based on it's type. If multiple services has registered the same type
	// then return the first one that's registered.
	//
	// @param type
	//			The service type
	// @return A reference created by the plugin engine if found; NULL otherwise
	virtual IPluginServiceReference1* GetServiceReference(const type_info& type) = 0;

	//
	// Retrieves a specific service reference based on it's type. If multiple services has registered the same type
	// then return the first one that's registered.
	//
	// @param type
	//			The service type
	// @param filter
	//			A search filter
	// @return A reference created by the plugin engine if found; NULL otherwise
	virtual IPluginServiceReference1* GetServiceReference(const type_info& type, const char* filter) = 0;

	//
	// Retrieves a all service reference implementing the supplied type. 
	//
	// @param type
	//			The service type
	// @param callback
	//			A callack instance
	virtual void GetServiceReferences(const type_info& type, IPluginServiceReferences1* callback) = 0;

	//
	// Retrieves a all service reference implementing the supplied type. 
	//
	// @param type
	//			The service type
	// @param filter
	//			A search filter
	// @param callback
	//			A callack instance
	virtual void GetServiceReferences(const type_info& type, const char* filter, IPluginServiceReferences1* callback) = 0;
};

#endif

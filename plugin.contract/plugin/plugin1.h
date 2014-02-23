#pragma once
#ifndef _IPLUGIN1_H_
#define _IPLUGIN1_H_

#include "pluginobject1.h"

//
// Interface representing the actual plugin. 
DECLARE_INTERFACE(IPlugin1, IPluginObject1)
{
	enum PLUGIN_API Status {
		//
		// Symbolizes that the plugin is starting up.
		STATUS_STARTING = 0,

		//
		// Symbolizes that the plugin is active and all it's services registered inside
		// the plugin engine
		STATUS_ACTIVE = 1,

		//
		// The plugin is stopping and is currently removing it's internal resources
		STATUS_STOPPING = 2,

		//
		// An inactive status means that the plugin engine is aware of the plugin but none of
		// the services are registrered.
		STATUS_STOPPED = 3,
	};

	//
	// Register a new plugin service. It is s the plugin that owns the memory of the service. This means 
	// that the plugin is responsible to clean the memory up during the STATUS_STOPPING phase. All services are automatically
	// unregistered during the plugins STATUS_STOPPING phase.
	//
	// @param type
	//			The type of the supplied service
	// @param service
	//			The service we want to register
	// @return A service reference placeholder object for the actual service
	virtual IPluginServiceReference1* RegisterService(const type_info& type, IPluginService1* service) = 0;

	//
	// Unregister all services of a specific type. All services are automatically
	// unregistered during the plugins STATUS_STOPPING phase.
	//
	// @param type
	//			The service type
	virtual void UnregisterServices(const type_info& type) = 0;

	//
	// Unregister a specific service. All services are automatically
	// unregistered during the plugins STATUS_STOPPING phase.
	//
	// @param reference
	//			The service reference we want to unregister
	virtual void UnregisterService(IPluginServiceReference1* reference) = 0;

	//
	// Add a service listener. This listener will receive events when services are registered and unregistered.
	// Listener bound to a plugin is automatically removed during the plugin's STATUS_STOPPING phase 
	//
	// @param listener
	//			The listener instance
	virtual void AddServiceListener(IPluginServiceListener1* listener) = 0;

	//
	// Remove a service listener. Listeners are automatically unregistrered during the plugins STATUS_STOPPING phase.
	//
	// @param listener
	virtual void RemoveServiceListener(IPluginServiceListener1* listener) = 0;

	//
	// Add a plugin listener. This listener will receive events when plugins are activated and deactivated.
	// Listener bound to a plugin is automatically removed during the plugin's STATUS_STOPPING phase 
	//
	// @param listener
	//			The listener instance
	virtual void AddPluginListener(IPluginListener1* listener) = 0;

	//
	// Remove a plugin listener. Listeners are automatically unregistrered during the plugins STATUS_STOPPING phase.
	//
	// @param listener
	virtual void RemovePluginListener(IPluginListener1* listener) = 0;

	//
	// @return The status for this plugin
	virtual Status GetStatus() const = 0;

	//
	// @return The version of this plugin.
	virtual const IPluginVersion1* GetVersion() const = 0;

	//
	// @return The context where this located in
	virtual IPluginContext1* GetPluginContext() = 0;

	//
	// @return A null-terminated name of the plugin.
	virtual const char* GetName() = 0;
};

#endif
#pragma once
#ifndef _PLUGIN_IPLUGIN_H_
#define _PLUGIN_IPLUGIN_H_

#include "defines.h"

namespace plugin
{
	class PLUGIN_API IVersion;

	class PLUGIN_API IPlugin
	{
	public:
		virtual ~IPlugin() {}

	public:
		//
		// @return The version of this plugin
		virtual const IVersion* GetVersion() const = 0;
	};
}

#endif
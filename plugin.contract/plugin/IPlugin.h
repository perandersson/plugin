#pragma once
#ifndef _PLUGIN_IPLUGIN_H_
#define _PLUGIN_IPLUGIN_H_

#include "defines.h"

namespace plugin
{
	class PLUGIN_API IPlugin
	{
	public:
		virtual ~IPlugin() {}
	};
}

#endif
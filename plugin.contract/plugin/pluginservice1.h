#pragma once
#ifndef _IPLUGIN_SERVICE1_H_
#define _IPLUGIN_SERVICE1_H_

#include "pluginobject1.h"

//
//
DECLARE_INTERFACE(IPluginService1, IPluginObject1)
{
};

#ifndef DEFINE_SERVICE
#define DEFINE_SERVICE(Type) DECLARE_INTERFACE(Type, IPluginService)
#endif

#endif

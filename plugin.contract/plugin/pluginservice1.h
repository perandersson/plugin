#pragma once
#ifndef _IPLUGIN_SERVICE1_H_
#define _IPLUGIN_SERVICE1_H_

#include "defines.h"

//
//
DEFINE_INTERFACE(IPluginService1, IPluginObject)
{
};

#ifndef DEFINE_SERVICE
#define DEFINE_SERVICE(Type) DEFINE_INTERFACE(Type, IPluginService)
#endif

#endif

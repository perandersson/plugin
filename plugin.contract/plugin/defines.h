#pragma once
#ifndef _PLUGIN_DEFINES_H_
#define _PLUGIN_DEFINES_H_

#include <typeinfo>

#define SSTRINGIFY(x) #x
#define STRINGIFY(x) SSTRINGIFY(x)

#ifdef PLUGIN_EXPORTS 
#ifndef PLUGIN_API
#define PLUGIN_API __declspec(dllexport)
#endif
#else
#ifndef PLUGIN_API
#define PLUGIN_API __declspec(dllimport)
#endif
#endif

#ifndef THREAD_LOCAL
#ifdef WIN32
#define THREAD_LOCAL __declspec(thread)
#else
#define THREAD_LOCAL __thread
#endif
#endif

#ifdef __GNUC__
typedef std::type_info type_info;
#endif

#ifndef DEFINE_INTERFACE
#define DEFINE_INTERFACE(Name, Inherits) \
struct PLUGIN_API Name : public Inherits
#endif

#ifndef DEFINE_INTERFACE_B
#define DEFINE_INTERFACE_B(Name) \
class PLUGIN_API Name
#endif

#ifndef DECLARE_INTERFACE
#define DECLARE_INTERFACE(Name) \
struct PLUGIN_API Name
#endif

DEFINE_INTERFACE_B(IPluginObject)
{
public:
	virtual ~IPluginObject() {}
};


#ifdef ENABLE_ONLY_MSVC
#if !_MSC_VER
#error You are building your code using another compiler than the MSVC, which has been approaved for your contract
#endif
#endif

#ifdef ENABLE_ONLY_GCC
#if !__GNUC__
#error You are building your code using another compiler than the GCC, which has been approaved for your contract
#endif
#endif

#ifdef ENABLE_ONLY_INTEL_COMPILER
#if !__INTEL_COMPILER
#error You are building your code using another compiler than the Intel Compiler, which has been approaved for your contract
#endif
#endif


#endif

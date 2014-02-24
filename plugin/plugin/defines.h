#pragma once
#ifndef _PLUGIN_DEFINES_H_
#define _PLUGIN_DEFINES_H_

#ifdef PLUGIN_EXPORTS 
#ifndef PLUGIN_API
#define PLUGIN_API __declspec(dllexport)
#endif
#else
#ifndef PLUGIN_API
#define PLUGIN_API __declspec(dllimport)
#endif
#endif

#ifdef PLUGIN_CONTRACT_EXPORTS
#ifndef PLUGIN_CONTRACT_API
#define PLUGIN_CONTRACT_API __declspec(dllexport)
#endif
#else
#ifndef PLUGIN_CONTRACT_API
#define PLUGIN_CONTRACT_API __declspec(dllimport)
#endif
#endif

//
// Declare all the interfaces used by the plugin engine
//

struct PLUGIN_API IPluginObject1;

typedef IPluginObject1 IPluginObject;
typedef IPluginObject1* PIPluginObject;

// A plugin object type
typedef long long PL_TYPE;

// A result returned by the plugin framework's interface.
typedef int PL_RES;

// A loaded plugin ID. Useful if we want to manually close any opened plugins
typedef unsigned int PL_LIBID;

// An error code delivered by the plugin framework
typedef int PL_ERRCODE;

// Symbolizes an unsigned long in the plugin framework
typedef unsigned long PL_UINT64;

#define PL_OK 1
#define PL_ERR 0


//
// Define a plugin object type ID (ID for this specific interface).
//
// @param Type
//			The interface type
// @param UID
//			A unique ID number. It's up to your project to select which ones you want. 
//			Numbers below 10 are restricted.
#define DEFINE_PLTYPE(Type, UID) static const PL_TYPE Type##_ID = UID##LL

//
// Retrieves a plugin object type ID unique to the supplied Type. You are also free to manually type in <Type>_ID if you want.
//
// @param Type
//			The type
#define PL_TYPEOF(Type) Type##_ID

#ifndef DECLARE_INTERFACE
#define DECLARE_INTERFACE(Name, Inherits) struct PLUGIN_API Name : public Inherits
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(Obj) if(Obj != nullptr) Obj->Release()
#endif

#ifndef FAILURE
#define FAILURE(X) ((X) == PL_ERR)
#endif

#ifndef SUCCESS
#define SUCCESS(X) ((X) == PL_OK)
#endif

//
// Error codes
//

// No error has occured
#define PL_ERRCODE_NOERROR 0

// The library was not found
#define PL_ERRCODE_LIBRARYNOTFOUND 1

// The entry point is missing inside the plugin
#define PL_ERRCODE_MISSINGENTRYPOINT 2

// Entry point returned failure
#define PL_ERRCODE_ENTRYPOINTFAILURE 3

// The object you are looking for is not found
#define PL_ERRCODE_OBJECTNOTFOUND 4

// The supplied PL_LIBID doesn't exist
#define PL_ERRCODE_NONEXISTENTLIBID 5

// You are trying to perform an action without an active plugin available
#define PL_ERRCODE_NOACTIVEPLUGIN 6

// You are trying to register a non-global object as a plugin, which is not allowed.
#define PL_ERRCODE_NOTHOSTERROR 7

// The plugin framework is not initialized
#define PL_ERRCODE_NOTINITIALIZED 8

// This error code happens if the host application tries to unload 
// a library that's currently in use (has object's with reference counter > 0).
#define PL_ERRCODE_LIBRARYINUSE 9

// Error code occures if retrieval of get objects fails by some reason
#define PL_ERRCODE_GETOBJECTSFAILED 10

// A supplied argument is invalid
#define PL_ERRCODE_INVALIDARGUMENT 11

#endif

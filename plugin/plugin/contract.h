#pragma once
#ifndef _PLUGIN_CONTRACT_H_
#define _PLUGIN_CONTRACT_H_

//
// This is the version 1 of the plugin library
//

#include "pluginobject1.h"


//
// Typedefs for prettier interface
//

// Function signature for when retrieving a list of plugin objects.
typedef PL_RES (*PIPluginObjectFunc)(PL_TYPE, PIPluginObject);

extern "C" {
	
	//
	// Initializes the plugin framework
	//
	// @return PL_OK if successfull; PL_ERR otherwise;
	extern PLUGIN_CONTRACT_API PL_RES Plugin1_Init();

	//
	// Releases the plugin frameworks internal resources
	//
	// @return PL_OK if successfull; PL_ERR otherwise;
	extern PLUGIN_CONTRACT_API PL_RES Plugin1_Release();

	//
	// Retrieves the latest error code
	//
	// @return The last error code encountered by the plugin framework
	extern PLUGIN_CONTRACT_API PL_ERRCODE Plugin1_GetLastError();

	//
	// Retrieves an object registered in the plugin framework. This increases the reference counter of the object
	// by invoking {@see IPluginObject1::AddRef}. If the plugin framework returns a valid pointer then you are
	// responsible for invoking the {@see IPluginObject1::Release} method when you are done.
	//
	// @param type
	//			The service type
	// @param _out_Ptr
	//			The memory location where we want to put the object into
	// @return PL_OK if successfull; PL_ERR otherwise;
	extern PLUGIN_CONTRACT_API PL_RES Plugin1_GetObject(PL_TYPE type, PIPluginObject* _out_Ptr);

	//
	// Retrieves all objects registered in the plugin framework by the given type. An object is automatically
	// referenced- and deferenced when entering and exiting the supplied function pointer. Unless, of course,
	// you are planning on saving the pointer somewhere. Then you are required to invoke AddRef.
	//
	// All other access to the object follows the same pattern as Plugin1_GetObject.
	//
	// @param type
	//			The service type
	// @param func
	//			The function we want to invoke for each object found
	// @return PL_OK if successfull; PL_ERR otherwise;
	extern PLUGIN_CONTRACT_API PL_RES Plugin1_GetObjects(PL_TYPE type, PIPluginObjectFunc func);

	//
	// Register a new object into the plugin framework
	//
	// @param type
	// @param ptr
	// @return PL_OK if successfull; PL_ERR otherwise;
	extern PLUGIN_CONTRACT_API PL_RES Plugin1_RegisterObject(PL_TYPE type, PIPluginObject ptr);

	//
	// Register a new global object in the plugin framework. This is done by the host application.
	// 
	// @param type
	//			The type of the object
	// @param ptr
	//			The pointer to the plugin object
	// @return PL_OK if successfull; PL_ERR otherwise
	extern PLUGIN_CONTRACT_API PL_RES Plugin1_RegisterGlobalObject(PL_TYPE type, PIPluginObject ptr);

	//
	// Load the supplied library
	//
	// @param filename
	//			A null-terminated string containing the path to the plugin
	// @return An non-zero identifier if successfull; PLRES_ERR otherwise;
	extern PLUGIN_CONTRACT_API PL_LIBID Plugin1_LoadLibrary(const char* filename);

	//
	// Unload the supplied library
	//
	// @param id
	//			The library id. This value is returned by the Plugin1_LoadLibrary function.
	// @return PL_OK if successfull; PL_ERR otherwise;
	extern PLUGIN_CONTRACT_API PL_RES Plugin1_UnloadLibrary(PL_LIBID id);
}

// Function signature for the entry-point of the plugin
typedef PL_RES(*Plugin1EntryPointFunc)();

#define Plugin_Init Plugin1_Init
#define Plugin_Release Plugin1_Release
#define Plugin_GetLastError Plugin1_GetLastError
#define Plugin_GetObject Plugin1_GetObject
#define Plugin_GetObjects Plugin1_GetObjects
#define Plugin_RegisterObject Plugin1_RegisterObject
#define Plugin_RegisterGlobalObject Plugin1_RegisterGlobalObject
#define Plugin_LoadLibrary Plugin1_LoadLibrary
#define Plugin_UnloadLibrary Plugin1_UnloadLibrary

#define PluginEntryPointFunc Plugin1EntryPointFunc

//
// Each plugin is required to supply an entry-point function for the plugin.
// It is the entry-point that registers- the neccessary services used inside
// the plugin framework
#define DEFINE_ENTRYPOINT(Function) \
extern "C" { \
	PLUGIN_API PL_RES __cdecl Plugin1_EntryPoint() { \
		return Function##(); \
	} \
}


#endif

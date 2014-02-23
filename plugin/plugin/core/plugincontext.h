#pragma once
#include "../contract.h"
#include <memory>
#include <list>

extern "C" {
	PLUGIN_CONTRACT_API PL_RES Plugin_Init();
	PLUGIN_CONTRACT_API PL_RES Plugin_Release();
	PLUGIN_CONTRACT_API PL_ERRCODE Plugin_GetLastError();
	PLUGIN_CONTRACT_API PL_RES Plugin_GetObject(PL_TYPE type, PIPluginObject* _out_Ptr);
	PLUGIN_CONTRACT_API PL_RES Plugin_RegisterObject(PL_TYPE type, PIPluginObject ptr);
	PLUGIN_CONTRACT_API PL_RES Plugin_GetObjects(PL_TYPE type, PIPluginObjectFunc func);
	PLUGIN_CONTRACT_API PL_RES Plugin_RegisterGlobalObject(PL_TYPE type, PIPluginObject ptr);
	PLUGIN_CONTRACT_API PL_LIBID Plugin_LoadLibrary(const char* filename);
	PLUGIN_CONTRACT_API PL_RES Plugin_UnloadLibrary(PL_LIBID id);
}
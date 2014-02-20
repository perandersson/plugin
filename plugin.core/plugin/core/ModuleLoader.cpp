#include "ModuleLoader.h"
using namespace plugin::core;

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

LibraryHandle ModuleLoader::GetLibraryHandle(const char* fileName)
{
	return LoadLibraryA(fileName);
}

void ModuleLoader::UnloadLibrary(LibraryHandle library)
{
	FreeLibrary((HMODULE)library);
}

void* ModuleLoader::GetFunctionPtr(LibraryHandle library, const char* name)
{
	FARPROC addr = GetProcAddress((HMODULE)library, name);
	return addr;
}

#else

#error Not implemented

#endif

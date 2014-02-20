#include "ModuleLoader.h"
#include <cassert>
using namespace plugin::core;

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

LibraryHandle ModuleLoader::GetLibraryHandle(const char* fileName)
{
	auto library = LoadLibraryA(fileName);
	assert(((PIMAGE_DOS_HEADER)library)->e_magic == IMAGE_DOS_SIGNATURE);

	return library;
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


std::vector<std::string> ModuleLoader::GetFunctionNames(LibraryHandle library)
{
	std::vector<std::string> functions;

	HMODULE lib = (HMODULE)library;	
	PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS)((BYTE *)lib + ((PIMAGE_DOS_HEADER)lib)->e_lfanew);
	assert(header->Signature == IMAGE_NT_SIGNATURE);
	assert(header->OptionalHeader.NumberOfRvaAndSizes > 0);

	PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY)((BYTE *)lib + header->
		OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	PVOID names = (BYTE *)lib + exports->AddressOfNames;
	for (DWORD i = 0; i < exports->NumberOfNames; i++) {
		char* cname = (char *)lib + ((DWORD *)names)[i];
		std::string name = std::string(cname);
		functions.push_back(name);
	}

	return functions;
}

#else

#error Not implemented

#endif

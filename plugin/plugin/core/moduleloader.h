#pragma once
#include <vector>

typedef void* LibraryHandle;

class ModuleLoader
{
public:
	//
	// Load the supplied library and return a library handle for it
	//
	// @param fileName
	//			The library filename
	// @return A library handle; NULL if no library could be loaded
	static LibraryHandle GetLibraryHandle(const char* fileName);

	//
	// Unload the supplied library
	//
	// @param library
	//			The library
	static void UnloadLibrary(LibraryHandle library);

	//
	// Load a function from the supplied library and return a library handle for it
	//
	// @param library
	//			The library
	// @param name
	//			The function name
	// @return A function if found; NULL if no function was found
	template<typename T>
	static T GetFunction(LibraryHandle library, const char* name) {
		void* ptr = GetFunctionPtr(library, name);
		if (ptr == nullptr)
			return nullptr;

		return reinterpret_cast<T>(ptr);
	}

	//
	// Retrieves a list of all exported functions in a library
	//
	// @param library
	//			The library
	// @return A list of all the functions exported into the supplied library.
	static std::vector<std::string> GetFunctionNames(LibraryHandle library);

private:
	static void* GetFunctionPtr(LibraryHandle library, const char* name);
};


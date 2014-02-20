#pragma once
#ifndef _PLUGIN_MODULE_LOADER_H_
#define _PLUGIN_MODULE_LOADER_H_

namespace plugin
{
	namespace core
	{
		typedef void* LibraryHandle;

		class ModuleLoader
		{
		public:
			static LibraryHandle GetLibraryHandle(const char* fileName);

			static void UnloadLibrary(LibraryHandle library);

			template<typename T>
			static T GetFunction(LibraryHandle library, const char* name) {
				void* ptr = GetFunctionPtr(library, name);
				if (ptr == nullptr)
					return nullptr;

				return reinterpret_cast<T>(ptr);
			}

		private:
			static void* GetFunctionPtr(LibraryHandle library, const char* name);
		};
	}
}

#endif


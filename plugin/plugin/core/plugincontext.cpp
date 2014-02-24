#include "plugincontext.h"
#include "moduleloader.h"
#include <algorithm>
#include <vector>
#include <atomic>

class ObjectReference
{
public:
	ObjectReference(PL_TYPE type, PIPluginObject object) : mType(type), mObject(object) {
		object->AddRef();
	}

	ObjectReference(const ObjectReference& lhs) : mType(lhs.mType), mObject(lhs.mObject) {
		mObject->AddRef();
	}

	~ObjectReference() {
		mObject->Release();
	}

	PL_TYPE GetType() const {
		return mType;
	}

	PIPluginObject GetObject() const {
		return mObject;
	}

private:
	PL_TYPE mType;
	PIPluginObject mObject;
};

typedef std::vector<std::shared_ptr<ObjectReference>> Objects;

class PluginLibrary
{
public:
	PluginLibrary(LibraryHandle handle, PL_LIBID id) : mHandle(handle), mID(id) {

	}

	~PluginLibrary() {
		mObjects.clear();
		if (mHandle != nullptr) {
			ModuleLoader::UnloadLibrary(mHandle);
			mHandle = nullptr;
		}
	}

	LibraryHandle GetHandle() const{
		return mHandle;
	}

	PL_LIBID GetID() const {
		return mID;
	}

	PIPluginObject GetObject(PL_TYPE type) {
		Objects::size_type size = mObjects.size();
		for (Objects::size_type i = 0; i < size; ++i) {
			auto ref = mObjects[i];
			if (ref->GetType() == type) {
				return ref->GetObject();
			}
		}
		return nullptr;
	}

	PL_RES GetObjects(PL_TYPE type, PIPluginObjectFunc func) {
		Objects::size_type size = mObjects.size();
		for (Objects::size_type i = 0; i < size; ++i) {
			auto ref = mObjects[i];
			if (ref->GetType() == type) {
				auto object = ref->GetObject();
				object->AddRef();
				auto res = (*func)(type, object);
				object->Release();
				if (res != PL_OK)
					return PL_ERR;
			}
		}
		return PL_OK;
	}

	void AddObject(PL_TYPE type, PIPluginObject object) {
		auto ref = std::shared_ptr<ObjectReference>(new ObjectReference(type, object));
		mObjects.push_back(ref);
	}

private:
	LibraryHandle mHandle;
	PL_LIBID mID;
	Objects mObjects;
};

typedef std::vector<std::shared_ptr<PluginLibrary>> Libraries;

class PluginContext
{
public:
	PluginContext() : mLastError(PL_ERRCODE_NOERROR), mNextID(1) {
	}

	PL_ERRCODE GetLastError() {
		return mLastError.load();
	}

	void SetLastError(PL_ERRCODE errorCode) {
		mLastError.exchange(errorCode);
	}

	PL_RES GetObject(PL_TYPE type, PIPluginObject* _out_Ptr) {
		if (type == 0 || _out_Ptr == nullptr) {
			SetLastError(PL_ERRCODE_INVALIDARGUMENT);
			return PL_ERR;
		}

		auto globalObject = GetGlobalObject(type);
		if (globalObject != nullptr) {
			globalObject->AddRef();
			*_out_Ptr = globalObject;
			return PL_OK;
		}

		// See if any libraries has exposed the supplied object
		Libraries::size_type size = mLibraries.size();
		for (Libraries::size_type i = 0; i < size; ++i) {
			auto object = mLibraries[i]->GetObject(type);
			if (object != nullptr) {
				object->AddRef();
				*_out_Ptr = object;
				return PL_OK;
			}
		}
		*_out_Ptr = nullptr;
		SetLastError(PL_ERRCODE_OBJECTNOTFOUND);
		return PL_ERR;
	}

	PL_RES GetObjects(PL_TYPE type, PIPluginObjectFunc func) {
		if (type == 0 || func == nullptr) {
			SetLastError(PL_ERRCODE_INVALIDARGUMENT);
			return PL_ERR;
		}

		auto res = GetGlobalObjects(type, func);
		if (res == PL_ERR) {
			SetLastError(PL_ERRCODE_GETOBJECTSFAILED);
			return PL_ERR;
		}

		// See if any libraries has exposed the supplied object
		Libraries::size_type size = mLibraries.size();
		for (Libraries::size_type i = 0; i < size; ++i) {
			res = mLibraries[i]->GetObjects(type, func);
			if (res == PL_ERR) {
				SetLastError(PL_ERRCODE_GETOBJECTSFAILED);
				return PL_ERR;
			}
		}

		return PL_OK;
	}

	PIPluginObject GetGlobalObject(PL_TYPE type) {
		Objects::size_type size = mGlobalObjects.size();
		for (Objects::size_type i = 0; i < size; ++i) {
			auto ref = mGlobalObjects[i];
			if (ref->GetType() == type) {
				return ref->GetObject();
			}
		}
		return nullptr;
	}

	PL_RES GetGlobalObjects(PL_TYPE type, PIPluginObjectFunc func) {
		Objects::size_type size = mGlobalObjects.size();
		for (Objects::size_type i = 0; i < size; ++i) {
			auto ref = mGlobalObjects[i];
			if (ref->GetType() == type) {
				auto object = ref->GetObject();
				object->AddRef();
				auto res = (*func)(type, object);
				object->Release();
				if (res == PL_ERR)
					return PL_ERR;
			}
		}
		return PL_OK;
	}

	PL_RES RegisterObject(PL_TYPE type, PIPluginObject ptr) {
		if (type == 0 || ptr == nullptr) {
			SetLastError(PL_ERRCODE_INVALIDARGUMENT);
			return PL_ERR;
		}

		auto currentLibrary = mCurrentLibrary.lock();
		if (currentLibrary.get() == nullptr) {
			SetLastError(PL_ERRCODE_NOACTIVEPLUGIN);
			return PL_ERR;
		}
		currentLibrary->AddObject(type, ptr);
		return PL_OK;
	}

	PL_RES RegisterGlobalObject(PL_TYPE type, PIPluginObject ptr) {
		if (type == 0 || ptr == nullptr) {
			SetLastError(PL_ERRCODE_INVALIDARGUMENT);
			return PL_ERR;
		}

		auto currentLibrary = mCurrentLibrary.lock();
		if (currentLibrary.get() != nullptr) {
			SetLastError(PL_ERRCODE_NOTHOSTERROR);
			return PL_ERR;
		}

		auto ref = std::shared_ptr<ObjectReference>(new ObjectReference(type, ptr));
		mGlobalObjects.push_back(ref);
		return PL_OK;
	}

	PL_LIBID LoadLibrary(const char* filename) {
		if (filename == nullptr) {
			SetLastError(PL_ERRCODE_INVALIDARGUMENT);
			return PL_ERR;
		}

		auto library = ModuleLoader::GetLibraryHandle(filename);
		if (library == nullptr) {
			SetLastError(PL_ERRCODE_LIBRARYNOTFOUND);
			return PL_ERR;
		}

		auto entryPoint = ModuleLoader::GetFunction<PluginEntryPointFunc>(library, "Plugin1_EntryPoint");
		if (entryPoint == nullptr) {
			ModuleLoader::UnloadLibrary(library);
			SetLastError(PL_ERRCODE_MISSINGENTRYPOINT);
			return PL_ERR;
		}

		PL_LIBID newID = mNextID++;
		auto ref = std::shared_ptr<PluginLibrary>(new PluginLibrary(library, newID));
		mCurrentLibrary = ref;
		PL_RES result = (*entryPoint)();
		mCurrentLibrary.reset();
		if (result == PL_ERR) {
			SetLastError(PL_ERRCODE_ENTRYPOINTFAILURE);
			return PL_ERR;
		}

		mLibraries.insert(mLibraries.begin(), ref);
		return newID;
	}

	PL_RES UnloadLibrary(PL_LIBID id) {
		if (id == 0) {
			SetLastError(PL_ERRCODE_INVALIDARGUMENT);
			return PL_ERR;
		}

		const Libraries::size_type size = mLibraries.size();
		if (size == 0) {
			SetLastError(PL_ERRCODE_NONEXISTENTLIBID);
			return PL_ERR;
		}

		// You are only allowd to remove libraries in the reverse order of
		// when you added them. Remember that the items are always added at the top (push_front).
		for (Libraries::size_type i = 0; i < size; ++i) {
			auto library = mLibraries[i];
			if (library->GetID() == id) {
				if (i != 0) {
					SetLastError(PL_ERRCODE_LIBRARYINUSE);
					return PL_ERR;
				}
				else {
					Libraries::iterator removeIt = mLibraries.begin() + i;
					mLibraries.erase(removeIt);
					return PL_OK;
				}
			}
		}

		SetLastError(PL_ERRCODE_NONEXISTENTLIBID);
		return PL_ERR;
	}

private:
	std::atomic<PL_ERRCODE> mLastError;
	std::atomic<PL_LIBID> mNextID;
	Libraries mLibraries;
	std::weak_ptr<PluginLibrary> mCurrentLibrary;
	Objects mGlobalObjects;
};

PluginContext* gPluginContext = nullptr;

PLUGIN_CONTRACT_API PL_RES Plugin_Init()
{
	if (gPluginContext != nullptr)
		return PL_ERR;

	gPluginContext = new PluginContext();
	return PL_OK;
}

PLUGIN_CONTRACT_API PL_RES Plugin_Release()
{
	if (gPluginContext == nullptr)
		return PL_ERR;

	delete gPluginContext;
	return PL_OK;
}

PLUGIN_CONTRACT_API PL_ERRCODE Plugin_GetLastError()
{
	if (gPluginContext == nullptr)
		return PL_ERRCODE_NOTINITIALIZED;

	return gPluginContext->GetLastError();
}

PLUGIN_CONTRACT_API PL_RES Plugin_GetObject(PL_TYPE type, PIPluginObject* _out_Ptr)
{
	if (gPluginContext == nullptr)
		return PL_ERR;
	
	return gPluginContext->GetObject(type, _out_Ptr);
}

PLUGIN_CONTRACT_API PL_RES Plugin_GetObjects(PL_TYPE type, PIPluginObjectFunc func)
{
	if (gPluginContext == nullptr)
		return PL_ERR;

	return gPluginContext->GetObjects(type, func);
}

PLUGIN_CONTRACT_API PL_RES Plugin_RegisterObject(PL_TYPE type, PIPluginObject ptr)
{
	if (gPluginContext == nullptr)
		return PL_ERR;

	return gPluginContext->RegisterObject(type, ptr);
}

PLUGIN_CONTRACT_API PL_RES Plugin_RegisterGlobalObject(PL_TYPE type, PIPluginObject ptr)
{
	if (gPluginContext == nullptr)
		return PL_ERR;

	return gPluginContext->RegisterGlobalObject(type, ptr);
}

PLUGIN_CONTRACT_API PL_LIBID Plugin_LoadLibrary(const char* filename)
{
	if (gPluginContext == nullptr)
		return PL_ERR;

	return gPluginContext->LoadLibrary(filename);
}

PLUGIN_CONTRACT_API PL_RES Plugin_UnloadLibrary(PL_LIBID id)
{
	if (gPluginContext == nullptr)
		return PL_ERR;

	return gPluginContext->UnloadLibrary(id);
}

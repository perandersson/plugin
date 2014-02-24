#include <iostream>
#include "../gameengine.contract/contract.h"
#include <cassert>

void StartGame()
{
	PL_RES res = PL_OK;

	PIPluginObject object;
	res = Plugin_GetObject(PL_TYPEOF(gameengine::IGame), &object); assert(SUCCESS(res));

	gameengine::IGame* game;
	res = object->ConvertToType(PL_TYPEOF(gameengine::IGame), (void**)&game); assert(SUCCESS(res));

	game->StartGame();

	SAFE_RELEASE(game);
	SAFE_RELEASE(object);
}

class HostAppService : public gameengine::IComponent
{
public:
	HostAppService() : mRefCount(1) {

	}

	virtual ~HostAppService() {

	}

	PL_UINT64 AddRef() {
		return mRefCount++;
	}

	PL_UINT64 Release() {
		if (--mRefCount == 0) {
			delete this;
			return 0;
		}
		return mRefCount;
	}

	PL_RES ConvertToType(PL_TYPE type, void** _out_Ptr) {
		if (type == PL_TYPEOF(gameengine::IComponent)) {
			*_out_Ptr = static_cast<IComponent*>(this);
			AddRef();
			return PL_OK;
		}
		*_out_Ptr = nullptr;
		return PL_ERR;
	}

	virtual void Update(float dt) {

	}

private:
	PL_UINT64 mRefCount;
};

int main()
{
	PL_RES res = PL_OK;

	// Initialize the plugin framework
	res = Plugin_Init(); assert(SUCCESS(res));

	// Register a service from host application (this program) and expose
	// it to the the loaded plugins
	res = Plugin_RegisterGlobalObject(PL_TYPEOF(gameengine::IComponent), new HostAppService()); assert(SUCCESS(res));

	// Load our custom libraries
	PL_LIBID customcomponent1_dll = Plugin_LoadLibrary("customcomponent1.dll"); assert(customcomponent1_dll != PL_ERR);
	PL_LIBID demo_dll = Plugin_LoadLibrary("demo.dll"); assert(demo_dll != PL_ERR);

	// Start the game!
	StartGame();

	// Unload libraries. This is done automatically by the Plugin_Release command.
	// You are only allowed to unload libraries that are not in use.
	res = Plugin_UnloadLibrary(demo_dll); assert(SUCCESS(res));
	res = Plugin_UnloadLibrary(customcomponent1_dll); assert(SUCCESS(res));

	// Release the plugin framework
	res = Plugin_Release(); assert(SUCCESS(res));

	return 0;
}

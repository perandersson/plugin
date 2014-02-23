#include <iostream>
#include "../gameengine.contract/contract.h"
#include <cassert>

void StartGame()
{
	PL_RES res = PL_RESOK;

	PIPluginObject object;
	res = Plugin_GetObject(PL_TYPEOF(gameengine::IGame), &object); assert(res == PL_RESOK);

	gameengine::IGame* game;
	res = object->ConvertToType(PL_TYPEOF(gameengine::IGame), (void**)&game); assert(res == PL_RESOK);

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
		mRefCount--;
		if (mRefCount == 0) delete this;
		return mRefCount;
	}

	PL_RES ConvertToType(PL_TYPE type, void** _out_Ptr) {
		if (type == PL_TYPEOF(gameengine::IComponent)) {
			*_out_Ptr = static_cast<IComponent*>(this);
			AddRef();
			return PL_RESOK;
		}
		*_out_Ptr = nullptr;
		return PL_RESERR;
	}

	virtual void Update(float dt) {

	}

private:
	PL_UINT64 mRefCount;
};

int main()
{
	PL_RES res = PL_RESOK;

	// Initialize the plugin framework
	res = Plugin_Init(); assert(res == PL_RESOK);

	// Register a service from host application (this program) and expose
	// it to the the loaded plugins
	res = Plugin_RegisterGlobalObject(PL_TYPEOF(gameengine::IComponent), new HostAppService()); assert(res == PL_RESOK);

	// Load our custom libraries
	res = Plugin_LoadLibrary("customcomponent1.dll"); assert(res == PL_RESOK);
	res = Plugin_LoadLibrary("demo.dll"); assert(res == PL_RESOK);

	// Start the game!
	StartGame();

	// Release the plugin framework
	res = Plugin_Release(); assert(res == PL_RESOK);

	return 0;
}

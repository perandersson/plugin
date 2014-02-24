#include "../gameengine.contract/contract.h"
#include "DemoGame.h"
#include <iostream>

#include <plugin/contract.h>

class InternalComponent : public gameengine::IComponent
{
public:
	InternalComponent() { counter = 0; }
	virtual ~InternalComponent() {}

	virtual void Update(float dt) {
		counter += dt;
	}

	float counter;
};

DemoGame* gGame;

PL_RES GetAllComponents(PL_TYPE type, PIPluginObject object) {
	gameengine::IComponent* component;
	if (object->ConvertToType(PL_TYPEOF(gameengine::IComponent), (void**)&component)) {
		gGame->AddComponent(component);
	}
	return PL_OK;
}

PL_RES MyEntryPoint() {
	gGame = new DemoGame();
	Plugin_RegisterObject(PL_TYPEOF(gameengine::IGame), gGame);

	Plugin_GetObjects(PL_TYPEOF(gameengine::IComponent), GetAllComponents);

	IPluginObject* ptr;
	if (Plugin_GetObject(PL_TYPEOF(gameengine::IComponent), &ptr)) {
		gameengine::IComponent* component;
		if (ptr->ConvertToType(PL_TYPEOF(gameengine::IComponent), (void**)&component)) {
			gGame->AddComponent(component);
		}
		ptr->Release();
	}

	return PL_OK;
}

DEFINE_ENTRYPOINT(MyEntryPoint);

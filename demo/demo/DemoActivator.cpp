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

class DemoActivator : public IPluginActivator, public IPluginServiceListener
{
public:
	DemoActivator() {

	}

	virtual ~DemoActivator() {

	}

	virtual void Start(IPluginContext* context, IPlugin* plugin) {
		plugin->AddServiceListener(this);
		plugin->RegisterService(typeid(gameengine::IGame), &mService);
		mService.AddInternalComponent(new InternalComponent());
	}

	virtual void Stop(IPlugin* plugin) {
		std::cout << "DemoActivator is deactivated" << std::endl;
	}

	virtual void OnServiceChanged(IPluginServiceReference* reference, Status status) {
		if (status == STATUS_REGISTERED) {
			const type_info& type = reference->GetType();
			if (type == typeid(gameengine::IComponent)) {
				auto component = dynamic_cast<gameengine::IComponent*>(reference->GetService());
				mService.AddComponent(component);
			}
		}
		std::cout << "DemoActivator -> Service status changed for type: " << reference->GetType().name() << std::endl;
	}
	
private:
	DemoGame mService;
};

DEFINE_PLUGIN(DemoActivator, "1.0.0");

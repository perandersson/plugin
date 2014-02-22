#include "../gameengine.contract/contract.h"
#include "CustomComponent1.h"
#include <iostream>

#include <plugin/contract.h>

class CustomComponent1Activator : public IPluginActivator, public IPluginServiceListener
{
public:
	CustomComponent1Activator() {

	}

	virtual ~CustomComponent1Activator() {

	}

	virtual void Start(IPluginContext* context, IPlugin* plugin) {
		plugin->AddServiceListener(this);
		plugin->RegisterService(typeid(gameengine::IComponent), &mService);
	}

	virtual void Stop(IPlugin* plugin) {
		std::cout << "CustomComponent1Activator is deactivated" << std::endl;
	}

	virtual void OnServiceChanged(IPluginServiceReference* reference, Status status) {
		std::cout << "CustomComponent1Activator -> Service status changed for type: " << reference->GetType().name() << std::endl;
	}

private:
	CustomComponent1 mService;
};

DEFINE_PLUGIN(CustomComponent1Activator, "1.0.0");

#include "../gameengine.contract/contract.h"
#include "CustomComponent1.h"
#include <iostream>

#include <plugin/contract.h>

class CustomComponent1Activator : public IPluginActivator1, public IPluginServiceListener1
{
public:
	CustomComponent1Activator() {

	}

	virtual ~CustomComponent1Activator() {

	}

	virtual void Start(IPluginContext1* context, IPluginBundle1* plugin) {
		plugin->AddServiceListener(this);
		plugin->RegisterService(typeid(gameengine::IComponent), &mService);
	}

	virtual void Stop(IPluginBundle1* plugin) {
		std::cout << "CustomComponent1Activator is deactivated" << std::endl;
	}

	virtual void OnServiceChanged(IPluginServiceReference1* reference, Status status) {
		std::cout << "CustomComponent1Activator -> Service status changed for type: " << reference->GetType().name() << std::endl;
	}

private:
	CustomComponent1 mService;
};

DEFINE_PLUGIN(CustomComponent1Activator, "1.0.0");

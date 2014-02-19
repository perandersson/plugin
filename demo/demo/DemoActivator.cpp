#include "../gameengine.contract/contract.h"
#include "DemoGame.h"
#include <iostream>

#include <plugin/contract.h>
using plugin::contract::IPluginActivator;
using plugin::contract::IServiceListener;
using plugin::contract::IServiceReference;
using plugin::contract::IPluginContext;
using plugin::contract::IPlugin;

class DemoActivator : public IPluginActivator, public IServiceListener
{
public:
	DemoActivator() {

	}

	virtual ~DemoActivator() {

	}

	virtual void Start(IPluginContext* context, IPlugin* plugin) {
		plugin->AddServiceListener(this);
		plugin->RegisterService(typeid(gameengine::IGame), &mService);
	}

	virtual void Stop(IPlugin* plugin) {
		std::cout << "DemoActivator is deactivated" << std::endl;
	}

	virtual void OnServiceChanged(IServiceReference* reference, Status status) {
		if (status == STATUS_REGISTERED) {
			const type_info& type = reference->GetType();
			if (type == typeid(gameengine::IGame)) {
				std::cout << "IGame instance registered!!" << std::endl;
			}
		}
		std::cout << "DemoActivator -> Service status changed for type: " << reference->GetType().name() << std::endl;
	}
	
private:
	DemoGame mService;
};

DEFINE_PLUGIN(DemoActivator, "1.0.0");

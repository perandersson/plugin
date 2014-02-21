#include "../gameengine.contract/contract.h"
#include "DemoGame.h"
#include <iostream>

#include <plugin/contract.h>

class DemoActivator : public IPluginActivator1, public IPluginServiceListener1
{
public:
	DemoActivator() {

	}

	virtual ~DemoActivator() {

	}

	virtual void Start(IPluginContext1* context, IPluginBundle1* plugin) {
		plugin->AddServiceListener(this);
		plugin->RegisterService(typeid(gameengine::IGame), &mService);
	}

	virtual void Stop(IPluginBundle1* plugin) {
		std::cout << "DemoActivator is deactivated" << std::endl;
	}

	virtual void OnServiceChanged(IPluginServiceReference1* reference, Status status) {
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

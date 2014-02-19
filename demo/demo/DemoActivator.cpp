#include <plugin/contract.h>
#include "../gameengine.contract/contract.h"
#include "DemoGame.h"
#include <iostream>

using namespace plugin::contract;

class DemoActivator : public IPluginActivator, public IServiceListener
{
public:
	DemoActivator() {

	}

	virtual ~DemoActivator() {

	}

	virtual void Start(IPluginContext& context, IPlugin& plugin) {
		plugin.AddServiceListener(this);
		plugin.RegisterService(typeid(gameengine::IGame), &mService);
	}

	virtual void Stop(IPlugin& plugin) {
		std::cout << "DemoActivator is deactivated" << std::endl;
	}

	virtual void OnServiceChanged(const type_info& type, IServiceReference& reference, Status status) {
		std::cout << "DemoActivator -> Service status changed for type: " << type.name() << std::endl;
	}
	
private:
	DemoGame mService;
};

DEFINE_PLUGIN(DemoActivator, "1.0.0");

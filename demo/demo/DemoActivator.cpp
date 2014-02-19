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

	virtual void Start(IPluginContext* context, IPlugin* plugin) {
		context->RegisterService(typeid(gameengine::IGame), &mService);
	}

	virtual void Stop(IPlugin* plugin) {
		std::cout << "DemoActivator is deactivated" << std::endl;
	}

	virtual void ServiceRegistered(IPluginContext& context, const type_info& type, IServiceReference& reference) {
		std::cout << "DemoActivator -> Service is registered of type: " << type.name() << std::endl;
	}

	virtual void ServiceUnregisted(IPluginContext& context, const type_info& type, const IServiceReference& service) {

	}

private:
	DemoGame mService;
};

DEFINE_PLUGIN(DemoActivator, "1.0.0");

#include <plugin/contract.h>
#include <iostream>

using namespace plugin;

class Plugin1Service : public IService
{
public:
};

class Plugin1Activator : public IPluginActivator, public IServiceListener
{
public:
	Plugin1Activator() {

	}

	virtual ~Plugin1Activator() {

	}

	virtual void Start(IPluginContext* context, IPlugin* plugin) {
		std::cout << "Plugin1 is activated" << std::endl;
		context->AddServiceListener(this);
		context->RegisterService(typeid(Plugin1Service), &mService);
	}

	virtual void Stop(IPlugin* plugin) {
		std::cout << "Plugin1 is deactivated" << std::endl;
	}

	virtual void ServiceRegistered(const type_info& type, IPluginContext* context, IServiceReference* reference) {
		std::cout << "Plugin1 -> Service is registered of type: " << type.name() << std::endl;
	}

	virtual void ServiceUnregisted(const type_info& type, IPluginContext* context, const IServiceReference* service) {

	}

private:
	Plugin1Service mService;
};

DEFINE_PLUGIN(Plugin1Activator);

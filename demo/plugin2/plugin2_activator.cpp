#include <plugin/contract.h>
#include <iostream>

using namespace plugin;

class Plugin2Service : public IService
{
public:
};

class Plugin2Activator : public IPluginActivator, public IServiceListener
{
public:
	Plugin2Activator() {

	}

	virtual ~Plugin2Activator() {

	}

	virtual void Start(IPluginContext* context, IPlugin* plugin) {
		std::cout << "Plugin2 is activated" << std::endl;
		context->AddServiceListener(this);
		context->RegisterService(typeid(Plugin2Service), &mService);
	}

	virtual void Stop(IPlugin* plugin) {
		std::cout << "Plugin2 is deactivated" << std::endl;
	}

	virtual void ServiceRegistered(const type_info& type, IPluginContext* context, IServiceReference* reference) {
		std::cout << "Plugin2 -> Service is registered of type: " << type.name() << std::endl;
	}

	virtual void ServiceUnregisted(const type_info& type, IPluginContext* context, const IServiceReference* service) {

	}

private:
	Plugin2Service mService;
};

DEFINE_PLUGIN(Plugin2Activator, "1.0.0");

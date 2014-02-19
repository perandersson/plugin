#include "PluginContext.h"
#include "ServiceReference.h"
#include "Plugin.h"
#include "Version.h"
#include <algorithm>

using namespace plugin;
using namespace plugin::core;

PluginContext::PluginContext()
{

}

PluginContext::~PluginContext()
{

}

void PluginContext::StartPlugin(IPluginActivator* activator, const Version& version)
{
	std::shared_ptr<Plugin> plugin(new Plugin(activator, version));
	mPlugins.push_back(plugin);
	plugin->Start(this);
}

void PluginContext::NotifyServiceChanged(ServiceReference* reference, IServiceListener::Status status)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		(*it)->NotifyServiceChanged(reference, status);
	}
}

IServiceReference* PluginContext::GetServiceReference(const type_info& type)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		ServiceReference* reference = (*it)->FindServiceReference(type);
		if (reference->IsValid()) {
			return reference;
		}
	}

	return &InvalidServiceReference::INSTANCE;
}

IService* PluginContext::GetService(IServiceReference* reference)
{
	ServiceReference* s = dynamic_cast<ServiceReference*>(reference);
	return s->GetService();
}

void PluginContext::UngetService(IServiceReference* reference)
{
	ServiceReference* s = dynamic_cast<ServiceReference*>(reference);
	s->UngetService();
}

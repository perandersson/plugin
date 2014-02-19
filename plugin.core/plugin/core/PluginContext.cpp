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
	std::shared_ptr<Plugin> plugin(new Plugin(*this, activator, version));
	mPlugins.push_back(plugin);
	plugin->Start(*this);
}

void PluginContext::NotifyServiceListeners(const type_info& type, ServiceReference& reference)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		(*it)->NotifyServiceListeners(*this, type, reference);
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

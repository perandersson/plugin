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

void PluginContext::StartPlugin(IPluginActivator* activator, const std::string& name, const Version& version)
{
	std::shared_ptr<Plugin> plugin(new Plugin(activator, name, version));
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

void PluginContext::NotifyPluginChanged(Plugin* plugin, IPluginListener::Status status)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		(*it)->NotifyPluginChanged(plugin, status);
	}
}

IServiceReference* PluginContext::GetServiceReference(const type_info& type)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		auto reference = (*it)->FindServiceReference(type);
		if (reference != nullptr) {
			return reference;
		}
	}

	return nullptr;
}

void PluginContext::GetServiceReferences(const type_info& type, IServiceReferences* callback)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		auto reference = (*it)->FindServiceReference(type);
		callback->OnServiceReference(reference);
	}
}

IService* PluginContext::GetService(IServiceReference* reference)
{
	if (reference == nullptr)
		return nullptr;

	ServiceReference* s = dynamic_cast<ServiceReference*>(reference);
	return s->GetService();
}

void PluginContext::UngetService(IServiceReference* reference)
{
	if (reference == nullptr)
		return;

	ServiceReference* s = dynamic_cast<ServiceReference*>(reference);
	s->UngetService();
}

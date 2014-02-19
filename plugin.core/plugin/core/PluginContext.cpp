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
	std::auto_ptr<IPluginActivator> activatorPtr(activator);
	std::shared_ptr<Plugin> plugin(new Plugin(activatorPtr, version));
	mCurrentPlugin = plugin;
	mPlugins.push_back(plugin);
	plugin->Start(this);
}

void PluginContext::RegisterService(const type_info& type, IService* service)
{
	auto reference = mCurrentPlugin->RegisterService(type, service);

	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		(*it)->NotifyServiceListeners(*this, type, *reference);
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

void PluginContext::AddServiceListener(IServiceListener* listener)
{
	mCurrentPlugin->AddServiceListener(listener);
}

void PluginContext::RemoveServiceListener(IServiceListener* listener)
{
	// TODO IMPLEMENT THIS!!!
}

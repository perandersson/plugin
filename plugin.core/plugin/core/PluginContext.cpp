#include "PluginContext.h"
#include "ServiceReference.h"
#include "Plugin.h"
#include <algorithm>

#ifdef _DEBUG
#include <iostream>
void Log(const char* msg) {
	std::cout << msg << std::endl;
}
#else
void Log(const char* msg) {
}
#endif

using namespace plugin;
using namespace plugin::core;

PluginContext::PluginContext()
{

}

PluginContext::~PluginContext()
{

}

void PluginContext::StartPlugin(IPluginActivator* activator)
{
	std::shared_ptr<Plugin> plugin(new Plugin(std::auto_ptr<IPluginActivator>(activator)));
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
		(*it)->NotifyServiceListeners(type, this, reference);
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

	return &ServiceReference::INVALID_SERVICE_REFERENCE;
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

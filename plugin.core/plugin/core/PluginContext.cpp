#include "plugincontext.h"
#include "servicereference.h"
#include "plugin.h"
#include "version.h"
#include "moduleloader.h"
#include <algorithm>

using namespace plugin;
using namespace plugin::core;

PluginContext::PluginContext()
{

}

PluginContext::~PluginContext()
{
	UnregisterPluginsList copy(mUnregistrationList);
	UnregisterPluginsList::iterator it = copy.begin();
	UnregisterPluginsList::const_iterator end = copy.end();
	for (; it != end; ++it) {
		(*it)->Stop();
	}
	mUnregistrationList.clear();
	mPlugins.clear();
}

void PluginContext::LoadPlugin(const char* fileName, const std::string& name)
{
	auto library = ModuleLoader::GetLibraryHandle(fileName);
	if (library == nullptr)
		return;

	//
	// 
	std::vector<std::string> functions = ModuleLoader::GetFunctionNames(library);

	//
	// Retrieves the activator function
	auto getPluginActivator = ModuleLoader::GetFunction<GetPluginActivator1Func>(library, "GetPluginActivator1");
	auto getPluginVersion = ModuleLoader::GetFunction<GetPluginVersionFunc>(library, "GetPluginVersion");
	if (getPluginActivator == nullptr || getPluginVersion == nullptr) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}

	IPluginActivator1* activator = (*getPluginActivator)();
	if (activator == nullptr) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}

	StartPlugin(library, activator, name, Version((*getPluginVersion)()));
}

void PluginContext::StartPlugin(LibraryHandle library, IPluginActivator1* activator, const std::string& name, const Version& version)
{
	std::shared_ptr<Plugin> plugin(new Plugin(library, activator, name, version));
	mPlugins.push_back(plugin);
	mUnregistrationList.push_front(plugin.get());
	plugin->Start(this);
}

void PluginContext::NotifyServiceChanged(ServiceReference* reference, IPluginServiceListener1::Status status)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		(*it)->NotifyServiceChanged(reference, status);
	}
}

void PluginContext::NotifyPluginChanged(Plugin* plugin, IPluginBundleListener1::Status status)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		(*it)->NotifyPluginChanged(plugin, status);
	}
}

IPluginServiceReference1* PluginContext::GetServiceReference(const type_info& type)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		auto reference = (*it)->FindServiceReference(type);
		if (reference != nullptr) {
			return reference;
		}
	}

	return &NoServiceReferenceFound::INSTANCE;
}

void PluginContext::GetServiceReferences(const type_info& type, IPluginServiceReferences1* callback)
{
	Plugins::iterator it = mPlugins.begin();
	Plugins::const_iterator end = mPlugins.end();
	for (; it != end; ++it) {
		auto reference = (*it)->FindServiceReference(type);
		callback->OnServiceReference(reference);
	}
}

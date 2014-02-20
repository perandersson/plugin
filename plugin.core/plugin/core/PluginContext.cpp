#include "PluginContext.h"
#include "ServiceReference.h"
#include "Plugin.h"
#include "Version.h"
#include "ModuleLoader.h"
#include <algorithm>

using namespace plugin;
using namespace plugin::core;

PluginContext::PluginContext()
{

}

PluginContext::~PluginContext()
{
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

	auto getPluginEngineMajorVersion = ModuleLoader::GetFunction<GetPluginEngineVersionFunc>(library, "GetPluginEngineVersion");
	auto getPluginActivator = ModuleLoader::GetFunction<GetPluginActivatorFunc>(library, "GetPluginActivator");
	auto getPluginVersion = ModuleLoader::GetFunction<GetPluginVersionFunc>(library, "GetPluginVersion");

	if (getPluginEngineMajorVersion == nullptr ||
		getPluginEngineMajorVersion == nullptr ||
		getPluginActivator == nullptr) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}

	Version expectedVersion((*getPluginEngineMajorVersion)());
	if (expectedVersion.GetMajor() != PLUGIN_ENGINE_CONTRACT_MAJOR_VERSION ||
		expectedVersion.GetMinor() != PLUGIN_ENGINE_CONTRACT_MINOR_VERSION) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}



	IPluginActivator* activator = (*getPluginActivator)();
	if (activator == nullptr) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}

	StartPlugin(library, activator, name, Version((*getPluginVersion)()));
}

void PluginContext::StartPlugin(LibraryHandle library, IPluginActivator* activator, const std::string& name, const Version& version)
{
	std::shared_ptr<Plugin> plugin(new Plugin(library, activator, name, version));
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

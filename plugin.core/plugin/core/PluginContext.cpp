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

}

void PluginContext::LoadPlugin(const char* fileName, const std::string& name)
{
	auto library = ModuleLoader::GetLibraryHandle(fileName);
	if (library == nullptr)
		return;

	auto getPluginEngineMajorVersion = ModuleLoader::GetFunction<GetPluginEngineMajorVersionFunc>(library, "GetPluginEngineMajorVersion");
	auto getPluginEngineMinorVersion = ModuleLoader::GetFunction<GetPluginEngineMinorVersionFunc>(library, "GetPluginEngineMinorVersion");
	auto getPluginActivator = ModuleLoader::GetFunction<GetPluginActivatorFunc>(library, "GetPluginActivator");
	auto getPluginVersion = ModuleLoader::GetFunction<GetPluginVersionFunc>(library, "GetPluginVersion");

	if (getPluginEngineMajorVersion == nullptr ||
		getPluginEngineMajorVersion == nullptr ||
		getPluginActivator == nullptr) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}

	int expectedMajorVersion = (*getPluginEngineMajorVersion)();
	if (expectedMajorVersion != PLUGIN_ENGINE_MAJOR_VERSION) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}

	IPluginActivator* activator = (*getPluginActivator)();
	if (activator == nullptr) {
		ModuleLoader::UnloadLibrary(library);
		return;
	}

	const char* pluginVersion = (*getPluginVersion)();
	int majorVersion = 0;
	int minorVersion = 0;
	int patchVersion = 0;
	if (pluginVersion != nullptr)
		sscanf(pluginVersion, "%d.%d.%d", &majorVersion, &minorVersion, &patchVersion);

	StartPlugin(activator, std::string(name), Version(majorVersion, minorVersion, patchVersion));
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

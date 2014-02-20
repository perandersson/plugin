#include "Plugin.h"
#include "ServiceReference.h"
#include "PluginContext.h"
#include "Version.h"

using namespace plugin;
using namespace plugin::contract;
using namespace plugin::core;

Plugin::Plugin(LibraryHandle library, IPluginActivator* activator, const std::string& name, const Version& version)
: mLibrary(library), mPluginContext(nullptr), mActivator(activator), mVersion(version), mStatus(STATUS_STOPPED), mName(name)
{

}

Plugin::~Plugin()
{
	ModuleLoader::UnloadLibrary(mLibrary);
	mLibrary = nullptr;
}

void Plugin::Start(PluginContext* context)
{
	mPluginContext = context;
	mStatus = STATUS_STARTING;
	mActivator->Start(context, this);
	mStatus = STATUS_ACTIVE;
	mPluginContext->NotifyPluginChanged(this, IPluginListener::STATUS_ACTIVE);
}

void Plugin::Stop()
{
	mStatus = STATUS_STOPPING;
	mActivator->Stop(this);
	mStatus = STATUS_STOPPED;
	mPluginContext->NotifyPluginChanged(this, IPluginListener::STATUS_INACTIVE);
}

ServiceReference* Plugin::FindServiceReference(const type_info& type)
{
	ServiceReferences::iterator it = mReferences.find(std::string(type.name()));
	if (it == mReferences.end()) {
		return nullptr;
	}

	return it->second.get();
}

IServiceReference* Plugin::RegisterService(const type_info& type, IService* service)
{
	std::string typeName(type.name());
	if (mReferences.find(typeName) != mReferences.end()) {
		// WHAT TO DO???
	}

	auto serviceReference = new ServiceReference(this, service, type);
	std::shared_ptr<ServiceReference> reference(serviceReference);
	mReferences.insert(std::make_pair(typeName, reference));

	// Notify all the registered service listeners about the new service
	mPluginContext->NotifyServiceChanged(serviceReference, IServiceListener::STATUS_REGISTERED);
	return serviceReference;
}

void Plugin::UnregisterServices(const type_info& type)
{
	std::string typeName(type.name());
	ServiceReferences::iterator it = mReferences.find(typeName);
	if (it == mReferences.end())
		return;

	//
	auto reference = it->second;
	mReferences.erase(it);
	mPluginContext->NotifyServiceChanged(reference.get(), IServiceListener::STATUS_UNREGISTERED);
}

void Plugin::UnregisterService(IServiceReference* reference)
{
	ServiceReferences::iterator it = mReferences.begin();
	ServiceReferences::const_iterator end = mReferences.end();
	for (; it != end; ++it) {
		if (it->second.get() == reference) {
			auto reference = it->second;
			mReferences.erase(it);
			mPluginContext->NotifyServiceChanged(reference.get(), IServiceListener::STATUS_UNREGISTERED);
			break;
		}
	}
}

void Plugin::AddServiceListener(IServiceListener* listener)
{
	mServiceListeners.push_back(listener);
}

void Plugin::RemoveServiceListener(IServiceListener* listener)
{
	ServiceListeners::iterator it = std::find(mServiceListeners.begin(), mServiceListeners.end(), listener);
	if (it != mServiceListeners.end())
		mServiceListeners.erase(it);
}

void Plugin::AddPluginListener(IPluginListener* listener)
{
	mPluginListeners.push_back(listener);
}

void Plugin::RemovePluginListener(IPluginListener* listener)
{
	PluginListeners::iterator it = std::find(mPluginListeners.begin(), mPluginListeners.end(), listener);
	if (it != mPluginListeners.end())
		mPluginListeners.erase(it);
}

void Plugin::NotifyServiceChanged(ServiceReference* reference, IServiceListener::Status status)
{
	ServiceListeners::iterator it = mServiceListeners.begin();
	ServiceListeners::const_iterator end = mServiceListeners.end();
	for (; it != end; ++it) {
		(*it)->OnServiceChanged(reference, status);
	}
}

void Plugin::NotifyPluginChanged(Plugin* plugin, IPluginListener::Status status)
{
	PluginListeners::iterator it = mPluginListeners.begin();
	PluginListeners::const_iterator end = mPluginListeners.end();
	for (; it != end; ++it) {
		(*it)->OnPluginChanged(plugin, status);
	}
}

IPlugin::Status Plugin::GetStatus() const
{
	return mStatus;
}

const IVersion* Plugin::GetVersion() const
{
	return &mVersion;
}

IPluginContext* Plugin::GetPluginContext()
{
	return mPluginContext;
}

const char* Plugin::GetName()
{
	return mName.c_str();
}

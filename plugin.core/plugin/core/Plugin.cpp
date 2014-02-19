#include "Plugin.h"
#include "ServiceReference.h"
#include "PluginContext.h"
#include "Version.h"

using namespace plugin;
using namespace plugin::contract;
using namespace plugin::core;

Plugin::Plugin(PluginContext& context, IPluginActivator* activator, const Version& version)
: mPluginContext(context), mActivator(activator), mVersion(version), mStatus(STATUS_STOPPED)
{

}

Plugin::~Plugin()
{

}

void Plugin::Start(PluginContext& context)
{
	mStatus = STATUS_STARTING;
	mActivator->Start(context, *this);
	mStatus = STATUS_ACTIVE;
}

void Plugin::Stop()
{
	mStatus = STATUS_STOPPING;
	mActivator->Stop(*this);
	mStatus = STATUS_STOPPED;	
}

ServiceReference* Plugin::FindServiceReference(const type_info& type)
{
	ServiceReferences::iterator it = mReferences.find(std::string(type.name()));
	if (it == mReferences.end()) {
		return &InvalidServiceReference::INSTANCE;
	}

	return it->second.get();
}

void Plugin::RegisterService(const type_info& type, IService* service)
{
	std::string typeName(type.name());
	if (mReferences.find(typeName) != mReferences.end()) {
		// WHAT TO DO???
	}

	auto serviceReference = new ServiceReference(this, service, type);
	std::shared_ptr<ServiceReference> reference(serviceReference);
	mReferences.insert(std::make_pair(typeName, reference));

	// Notify all the registered service listeners about the new service
	mPluginContext.NotifyServiceListeners(type, *serviceReference);
}

void Plugin::AddServiceListener(IServiceListener* listener)
{
	mListeners.push_back(listener);
}

void Plugin::RemoveServiceListener(IServiceListener* listener)
{
	ServiceListeners::iterator it = std::find(mListeners.begin(), mListeners.end(), listener);
	if (it != mListeners.end())
		mListeners.erase(it);
}

void Plugin::NotifyServiceListeners(PluginContext& context, const type_info& type, ServiceReference& reference)
{
	ServiceListeners::iterator it = mListeners.begin();
	ServiceListeners::const_iterator end = mListeners.end();
	for (; it != end; ++it) {
		(*it)->ServiceRegistered(context, type, reference);
	}
}

IPlugin::Status Plugin::GetStatus() const
{
	return mStatus;
}

const IVersion& Plugin::GetVersion() const
{
	return mVersion;
}

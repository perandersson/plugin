#include "Plugin.h"
#include "ServiceReference.h"
#include "PluginContext.h"
#include "Version.h"

using namespace plugin;
using namespace plugin::core;

Plugin Plugin::INVALID_PLUGIN;

Plugin::Plugin()
: mVersion(std::auto_ptr<Version>(new Version(0, 0, 0)))
{
}

Plugin::Plugin(std::auto_ptr<IPluginActivator> activator, std::auto_ptr<Version> version)
: mActivator(activator), mVersion(version)
{

}

Plugin::~Plugin()
{

}

bool Plugin::IsValid() const
{
	return this == &INVALID_PLUGIN;
}

void Plugin::Start(PluginContext* context)
{
	mActivator->Start(context, this);
}

void Plugin::Stop()
{
	mActivator->Stop(this);
}

ServiceReference* Plugin::FindServiceReference(const type_info& type)
{
	ServiceReferences::iterator it = mReferences.find(std::string(type.name()));
	if (it == mReferences.end()) {
		return &ServiceReference::INVALID_SERVICE_REFERENCE;
	}

	return it->second.get();
}

ServiceReference* Plugin::RegisterService(const type_info& type, IService* service)
{
	std::shared_ptr<ServiceReference> reference(new ServiceReference(this, service));
	mReferences.insert(std::make_pair(std::string(type.name()), reference));
	return reference.get();
}

void Plugin::NotifyServiceListeners(const type_info& type, PluginContext* context, ServiceReference* reference)
{
	ServiceListeners::iterator it = mListeners.begin();
	ServiceListeners::const_iterator end = mListeners.end();
	for (; it != end; ++it) {
		(*it)->ServiceRegistered(type, context, reference);
	}
}

void Plugin::AddServiceListener(IServiceListener* listener)
{
	mListeners.push_back(listener);
}

const IVersion* Plugin::GetVersion() const
{
	return mVersion.get();
}

#include "ServiceReference.h"
#include "Plugin.h"

using namespace plugin;
using namespace plugin::core;

ServiceReference ServiceReference::INVALID_SERVICE_REFERENCE;

ServiceReference::ServiceReference()
: mPlugin(nullptr), mService(nullptr), mNumReferences(0)
{

}

ServiceReference::ServiceReference(Plugin* plugin, IService* service)
: mPlugin(plugin), mService(service), mNumReferences(0)
{

}

ServiceReference::~ServiceReference()
{

}

bool ServiceReference::IsValid() const
{
	return this == &INVALID_SERVICE_REFERENCE;
}

IService* ServiceReference::GetService()
{
	if (!IsValid())
		return nullptr;

	mNumReferences++;
	return mService;
}

void ServiceReference::UngetService()
{
	if (!IsValid())
		return;

	mNumReferences--;
}

IPlugin* ServiceReference::GetPlugin()
{
	return mPlugin;
}

const IPlugin* ServiceReference::GetPlugin() const
{
	return mPlugin;
}

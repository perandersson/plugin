#include "ServiceReference.h"
#include "Plugin.h"

using namespace plugin;
using namespace plugin::core;

ServiceReference::ServiceReference(Plugin* plugin, IService* service, const type_info& type)
: mPlugin(plugin), mService(service), mNumReferences(0), mType(type)
{

}

ServiceReference::~ServiceReference()
{

}

bool ServiceReference::IsValid() const
{
	return this != &InvalidServiceReference::INSTANCE;
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

IPlugin& ServiceReference::GetPlugin()
{
	return *mPlugin;
}

const IPlugin& ServiceReference::GetPlugin() const
{
	return *mPlugin;
}

const type_info& ServiceReference::GetType() const
{
	return mType;
}

/////////////////////////////

InvalidServiceReference InvalidServiceReference::INSTANCE;

InvalidServiceReference::InvalidServiceReference()
: ServiceReference(nullptr, nullptr, typeid(InvalidServiceReference))
{

}

InvalidServiceReference::~InvalidServiceReference()
{

}

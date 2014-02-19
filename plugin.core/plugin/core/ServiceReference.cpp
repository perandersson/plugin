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

IService* ServiceReference::GetService()
{
	mNumReferences++;
	return mService;
}

void ServiceReference::UngetService()
{
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

const type_info& ServiceReference::GetType() const
{
	return mType;
}

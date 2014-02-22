#include "servicereference.h"
#include "plugin.h"

using namespace plugin;
using namespace plugin::core;

ServiceReference::ServiceReference(Plugin* plugin, IPluginService* service, const type_info& type)
: mPlugin(plugin), mService(service), mNumReferences(0), mType(type)
{

}

ServiceReference::~ServiceReference()
{

}

IPluginService* ServiceReference::GetService()
{
	if (mService == nullptr)
		return nullptr;

	mNumReferences++;
	return mService;
}

void ServiceReference::Release()
{
	if (mService == nullptr)
		return;

	mNumReferences--;
	if (mNumReferences) {
		mPlugin = nullptr;
		mService = nullptr;
	}
}

IPlugin* ServiceReference::GetPlugin()
{
	return mPlugin;
}

const IPlugin* ServiceReference::GetPlugin() const
{
	return mPlugin;
}

NoServiceReferenceFound NoServiceReferenceFound::INSTANCE;

const type_info& ServiceReference::GetType() const
{
	return mType;
}

NoServiceReferenceFound::NoServiceReferenceFound()
: ServiceReference(nullptr, nullptr, typeid(NoServiceReferenceFound))
{

}

NoServiceReferenceFound::~NoServiceReferenceFound()
{

}

#pragma once
#ifndef _CORE_SERVICE_REFERENCE_H_
#define _CORE_SERVICE_REFERENCE_H_

#include <plugin/contract.h>

namespace plugin
{
	namespace core
	{
		class Plugin;

		class ServiceReference : public IPluginServiceReference
		{
		public:
			ServiceReference(Plugin* plugin, IPluginService* service, const type_info& type);
			virtual ~ServiceReference();

		// IServiceReference
		public:
			virtual IPluginBundle* GetPlugin();
			virtual const IPluginBundle* GetPlugin() const;
			virtual const type_info& GetType() const;
			virtual IPluginService* GetService();
			virtual void Release();

		private:
			Plugin* mPlugin;
			IPluginService* mService;
			int mNumReferences;
			const type_info& mType;
		};

		class NoServiceReferenceFound : public ServiceReference
		{
		public:
			NoServiceReferenceFound();
			virtual ~NoServiceReferenceFound();

			static NoServiceReferenceFound INSTANCE;
		};
	}
}

#endif

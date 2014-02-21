#pragma once
#ifndef _CORE_SERVICE_REFERENCE_H_
#define _CORE_SERVICE_REFERENCE_H_

#include <plugin/contract.h>

namespace plugin
{
	namespace core
	{
		class Plugin;

		class ServiceReference : public IPluginServiceReference1
		{
		public:
			ServiceReference(Plugin* plugin, IPluginService1* service, const type_info& type);
			virtual ~ServiceReference();

		// IServiceReference
		public:
			virtual IPluginBundle1* GetPlugin();
			virtual const IPluginBundle1* GetPlugin() const;
			virtual const type_info& GetType() const;
			virtual IPluginService1* GetService();
			virtual void Release();

		private:
			Plugin* mPlugin;
			IPluginService1* mService;
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

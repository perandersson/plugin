#pragma once
#ifndef _CORE_SERVICE_REFERENCE_H_
#define _CORE_SERVICE_REFERENCE_H_

#include <plugin/contract.h>

namespace plugin
{
	using namespace contract;

	namespace core
	{
		class Plugin;

		class ServiceReference : public IServiceReference
		{
		public:
			ServiceReference(Plugin* plugin, IService* service, const type_info& type);
			virtual ~ServiceReference();

		// IServiceReference
		public:
			virtual IPlugin* GetPlugin();
			virtual const IPlugin* GetPlugin() const;
			virtual const type_info& GetType() const;
			virtual IService* GetService();
			virtual void Release();

		private:
			Plugin* mPlugin;
			IService* mService;
			int mNumReferences;
			const type_info& mType;
		};
	}
}

#endif

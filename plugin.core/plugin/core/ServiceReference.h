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

			//
			// @return TRUE if this service reference is valid; FALSE otherwise
			bool IsValid() const;

			//
			// Retrieves the service for this reference and increase it's reference counter
			//
			// @return The pointer to the service
			IService* GetService();

			//
			// Returns the pointer and decrease the reference counter for the supplied service
			void UngetService();

		// IServiceReference
		public:
			virtual IPlugin* GetPlugin();
			virtual const IPlugin* GetPlugin() const;
			virtual const type_info& GetType() const;

		private:
			Plugin* mPlugin;
			IService* mService;
			int mNumReferences;
			const type_info& mType;
		};

		//
		// Type indicating that the service reference is invalid/doesn't exist.
		class InvalidServiceReference : public ServiceReference
		{
		public:
			InvalidServiceReference();
			virtual ~InvalidServiceReference();

		public:
			static InvalidServiceReference INSTANCE;
		};
	}
}

#endif

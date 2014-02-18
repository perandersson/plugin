#pragma once
#ifndef _CORE_SERVICE_REFERENCE_H_
#define _CORE_SERVICE_REFERENCE_H_

#include <plugin/contract.h>

namespace plugin
{
	namespace core
	{
		class Plugin;

		class ServiceReference : public IServiceReference
		{
		public:
			ServiceReference();
			ServiceReference(Plugin* plugin, IService* service);
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

		public:
			// Instance that symbolizes that a service reference doesn't exist
			static ServiceReference INVALID_SERVICE_REFERENCE;

		private:
			Plugin* mPlugin;
			IService* mService;
			int mNumReferences;
		};
	}
}

#endif

#pragma once
#ifndef _PLUGIN_SERVICE_REFERENCES_H_
#define _PLUGIN_SERVICE_REFERENCES_H_

#include "defines.h"

namespace plugin
{
	namespace contract
	{
		class PLUGIN_API IServiceReference;

		//
		//
		class PLUGIN_API IServiceReferences
		{
		public:
			//
			//
			virtual void OnServiceReference(IServiceReference* reference) = 0;
		};
	}
}

#endif


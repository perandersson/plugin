#pragma once
#ifndef _PLUGIN_IVERSION_H_
#define _PLUGIN_IVERSION_H_

#include "defines.h"

namespace plugin
{
	namespace contract
	{
		//
		//
		class PLUGIN_API IVersion
		{
		public:
			virtual ~IVersion() {}

		public:
			//
			// @return The major component of this version instance
			virtual int GetMajor() const = 0;

			//
			// @return The minor component of this version instance
			virtual int GetMinor() const = 0;

			//
			// @return The patch component of this version instance
			virtual int GetPatch() const = 0;
		};
	}
}

#endif

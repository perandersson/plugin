#pragma once
#ifndef _PLUGIN_ICONTRACT_H_
#define _PLUGIN_ICONTRACT_H_

namespace plugin
{
	namespace contract
	{
		//
		// 
		class IContract
		{
		public:
			virtual ~IContract() {}

		public:
			virtual int GetMajorVersion() const = 0;
			
			virtual int GetMinorVersion() const = 0;

			virtual int GetPatchVersion() const = 0;

			virtual const type_info& GetType() const = 0;
		};
	}
}

#endif

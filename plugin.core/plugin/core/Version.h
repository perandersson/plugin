#pragma once
#ifndef _CORE_VERSION_H_
#define _CORE_VERSION_H_

#include <plugin/contract.h>

namespace plugin
{
	namespace core
	{
		class Version : public IVersion
		{
		public:
			Version(int major, int minor, int patch);
			~Version();

		// IVersion
		public:
			virtual int GetMajor() const;
			virtual int GetMinor() const;
			virtual int GetPatch() const;

		private:
			int mMajor;
			int mMinor;
			int mPatch;
		};
	}
}

#endif

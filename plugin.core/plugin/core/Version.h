#pragma once
#ifndef _CORE_VERSION_H_
#define _CORE_VERSION_H_

#include <plugin/contract.h>

namespace plugin
{
	using namespace contract;

	namespace core
	{
		class Version : public IVersion
		{
		public:
			Version(const char* version);
			Version(const Version& version);
			Version(int major, int minor, int patch);
			~Version();

			Version& operator = (const Version& lhs);

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

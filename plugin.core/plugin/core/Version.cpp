#include "Version.h"

using namespace plugin;
using namespace plugin::core;

Version::Version(const Version& version)
: mMajor(version.mMajor), mMinor(version.mMinor), mPatch(version.mPatch)
{

}

Version::Version(int major, int minor, int patch)
: mMajor(major), mMinor(minor), mPatch(patch)
{

}

Version::~Version()
{

}

Version& Version::operator = (const Version& lhs)
{
	mMajor = lhs.mMajor;
	mMinor = lhs.mMinor;
	mPatch = lhs.mPatch;
	return *this;
}

int Version::GetMajor() const
{
	return mMajor;
}

int Version::GetMinor() const
{
	return mMinor;
}

int Version::GetPatch() const
{
	return mPatch;
}

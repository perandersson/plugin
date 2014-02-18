#include "Version.h"

using namespace plugin;
using namespace plugin::core;

Version::Version(int major, int minor, int patch)
: mMajor(major), mMinor(minor), mPatch(patch)
{

}

Version::~Version()
{

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

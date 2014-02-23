#include "CustomComponent1.h"
#include <iostream>

CustomComponent1::CustomComponent1() : mRefCount(0)
{
	total = 0;
}

CustomComponent1::~CustomComponent1()
{

}

void CustomComponent1::Update(float dt)
{
	//std::cout << "Updating CustomComponent1: " << dt << std::endl;
	total += dt;
}

PL_UINT64 CustomComponent1::AddRef()
{
	mRefCount++;
	return mRefCount;
}

PL_UINT64 CustomComponent1::Release()
{
	mRefCount--;
	if (mRefCount <= 0) delete this;
	return mRefCount;
}

PL_RES CustomComponent1::ConvertToType(PL_TYPE type, void** _out_Ptr)
{
	if (type == PL_TYPEOF(gameengine::IComponent)) {
		*_out_Ptr = static_cast<IComponent*>(this); 
		AddRef();
		return PL_RESOK;
	}
	*_out_Ptr = nullptr;
	return PL_RESERR;
}

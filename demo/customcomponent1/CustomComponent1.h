#pragma once
#include "../gameengine.contract/contract.h"

class CustomComponent1 : public gameengine::IComponent
{
public:
	CustomComponent1();
	virtual ~CustomComponent1();

public:
	virtual void Update(float dt);
	virtual PL_UINT64 AddRef();
	virtual PL_UINT64 Release();
	virtual PL_RES ConvertToType(PL_TYPE type, void** _out_Ptr);

private:
	float total;
	int mRefCount;
};

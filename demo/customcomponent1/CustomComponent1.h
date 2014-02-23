#pragma once

#include "../gameengine.contract/contract.h"

class CustomComponent1 : public gameengine::IComponent
{
public:
	CustomComponent1();
	virtual ~CustomComponent1();

public:
	virtual void Update(float dt);

private:
	float total;
};

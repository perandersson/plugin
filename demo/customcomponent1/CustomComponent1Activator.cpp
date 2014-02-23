#include "../gameengine.contract/contract.h"
#include "CustomComponent1.h"
#include <iostream>

#include <plugin/contract.h>

PL_RES MyEntryPoint() {
	PL_RES res = Plugin_RegisterObject(PL_TYPEOF(gameengine::IComponent), new CustomComponent1());
	return res;
}

DEFINE_ENTRYPOINT(MyEntryPoint);
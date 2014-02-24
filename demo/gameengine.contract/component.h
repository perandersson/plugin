#pragma once
#include <plugin/contract.h>

namespace gameengine
{
	//
	// The actual game instance
	DECLARE_INTERFACE(IComponent, 9343021366, IPluginObject)
	{
		virtual void Update(float dt) = 0;
	};
}

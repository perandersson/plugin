#pragma once
#include <plugin/contract.h>

namespace gameengine
{
	//
	// The actual game instance
	DECLARE_INTERFACE(IComponent, IPluginObject)
	{
		virtual void Update(float dt) = 0;
	};

	DEFINE_PLTYPE(IComponent, 9343021366);
}

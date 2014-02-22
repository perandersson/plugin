#pragma once
#ifndef _GAMEENGINE_ICOMPONENT_H_
#define _GAMEENGINE_ICOMPONENT_H_

#define ENABLE_ONLY_MSVC
#include <plugin/contract.h>

namespace gameengine
{
	//
	// The actual game instance
	DEFINE_SERVICE(IComponent)
	{
		virtual void Update(float dt) = 0;
	};
}

#endif

#pragma once
#include <plugin/contract.h>

namespace gameengine
{
	//
	// The actual game instance
	DECLARE_INTERFACE(IGame, 800200966, IPluginObject)
	{
		virtual void StartGame() = 0;
	};
}

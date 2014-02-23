#pragma once
#include <plugin/contract.h>

namespace gameengine
{
	//
	// The actual game instance
	DECLARE_INTERFACE(IGame, IPluginObject)
	{
		virtual void StartGame() = 0;
	};

	DEFINE_PLTYPE(IGame, 800200966);
}

#pragma once
#ifndef _GAMEENGINE_IGAME_H_
#define _GAMEENGINE_IGAME_H_

#define ENABLE_ONLY_MSVC
#include <plugin/contract.h>

namespace gameengine
{
	//
	// The actual game instance
	DEFINE_SERVICE(IGame)
	{
		virtual void StartGame() = 0;
	};
}

#endif

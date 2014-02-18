#pragma once
#ifndef _GAMEENGINE_IGAME_H_
#define _GAMEENGINE_IGAME_H_

#include <plugin/contract.h>

namespace gameengine
{
	//
	// The actual game instance
	class IGame : public plugin::IService
	{
	public:
		virtual void StartGame() = 0;
	};
}

#endif

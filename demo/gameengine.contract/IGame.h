#pragma once
#ifndef _GAMEENGINE_IGAME_H_
#define _GAMEENGINE_IGAME_H_

#include <plugin/contract.h>

using namespace plugin::contract;

namespace gameengine
{
	//
	// The actual game instance
	class IGame : public IService
	{
	public:
		virtual void StartGame() = 0;
	};
}

#endif

#pragma once

#include "../gameengine.contract/contract.h"

class DemoGame : public gameengine::IGame
{
public:
	DemoGame();
	virtual ~DemoGame();

public:
	virtual void StartGame();
};
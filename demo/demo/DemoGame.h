#pragma once

#include "../gameengine.contract/contract.h"
#include <list>


class DemoGame : public gameengine::IGame
{
public:
	DemoGame();
	virtual ~DemoGame();

	void AddInternalComponent(gameengine::IComponent* component);
	void AddComponent(gameengine::IComponent* component);


public:
	virtual void StartGame();

private:
	std::list<gameengine::IComponent*> mComponents;
	std::list<gameengine::IComponent*> mInternalComponents;

};
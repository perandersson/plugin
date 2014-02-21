#include "DemoGame.h"
#include <iostream>

DemoGame::DemoGame()
{

}

DemoGame::~DemoGame()
{

}

void DemoGame::AddComponent(gameengine::IComponent* component)
{
	mComponents.push_back(component);
}

void DemoGame::StartGame()
{
	std::cout << "Starting demogame" << std::endl;
	std::list<gameengine::IComponent*>::iterator it = mComponents.begin();
	std::list<gameengine::IComponent*>::iterator end = mComponents.end();
	for (; it != end; ++it) {
		(*it)->Update(0.1f);
	}
}


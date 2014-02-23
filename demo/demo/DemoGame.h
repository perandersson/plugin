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

	virtual PL_UINT64 AddRef();
	virtual PL_UINT64 Release();
	virtual PL_RES ConvertToType(PL_TYPE type, void** _out_Ptr);

private:
	std::list<gameengine::IComponent*> mComponents;
	std::list<gameengine::IComponent*> mInternalComponents;

	PL_UINT64 mRefCount;
};
#include "DemoGame.h"
#include <iostream>
#include <Windows.h>

DemoGame::DemoGame() :mRefCount(0)
{

}

DemoGame::~DemoGame()
{
	std::list<gameengine::IComponent*>::iterator it = mComponents.begin();
	std::list<gameengine::IComponent*>::iterator end = mComponents.end();
	for (; it != end; ++it) {
		(*it)->Release();
	}
}

void DemoGame::AddComponent(gameengine::IComponent* component)
{
	mComponents.push_back(component);
}

void DemoGame::AddInternalComponent(gameengine::IComponent* component)
{
	mInternalComponents.push_back(component);
}

void DemoGame::StartGame()
{
	std::cout << "Starting demogame" << std::endl;
	DWORD systime = GetTickCount();

#ifdef _DEBUG
	for (int i = 0; i < 1000000; i++) {
#else
	for (int i = 0; i < 100000000; i++) {
#endif
		std::list<gameengine::IComponent*>::iterator it = mComponents.begin();
		std::list<gameengine::IComponent*>::iterator end = mComponents.end();
		for (; it != end; ++it) {
			(*it)->Update(0.1f);
		}
	}
	DWORD systime2 = GetTickCount();

	DWORD systime3 = GetTickCount();
#ifdef _DEBUG
	for (int i = 0; i < 1000000; i++) {
#else
	for (int i = 0; i < 100000000; i++) {
#endif
		std::list<gameengine::IComponent*>::iterator it = mInternalComponents.begin();
		std::list<gameengine::IComponent*>::iterator end = mInternalComponents.end();
		for (; it != end; ++it) {
			(*it)->Update(0.1f);
		}
	}
	DWORD systime4 = GetTickCount();

	std::cout << "External time: " << systime2 - systime << ", Internal time: " << systime4 - systime3 << std::endl;
}


PL_UINT64 DemoGame::AddRef()
{
	mRefCount++;
	return mRefCount;
}

PL_UINT64 DemoGame::Release()
{
	if (--mRefCount == 0) {
		delete this;
		return 0;
	}
	return mRefCount;
}

PL_RES DemoGame::ConvertToType(PL_TYPE type, void** _out_Ptr)
{
	if (_out_Ptr == nullptr)
		return PL_ERR;

	if (type == PL_TYPEOF(gameengine::IGame)) {
		*_out_Ptr = static_cast<IGame*>(this);
		AddRef();
		return PL_OK;
	}
	*_out_Ptr = nullptr;
	return PL_ERR;
}

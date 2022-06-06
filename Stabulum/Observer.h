#pragma once

#include "../BurgerTime/GameEvent.h"

class GameObject;

class Observer
{
public:
	Observer();
	virtual ~Observer() = default;

	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;

	virtual void OnNotify(GameObject* pGameObject, const GameEvent& event) = 0;

protected:
	bool m_HasComponentsCached;
};
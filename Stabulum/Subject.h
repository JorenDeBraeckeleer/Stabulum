#pragma once

#include <vector>
#include "Observer.h"

class GameObject;

class Subject
{
public:
	Subject() = default;

	virtual ~Subject() = default;
	Subject(const Subject& other) = delete;
	Subject(Subject&& other) = delete;
	Subject& operator=(const Subject& other) = delete;
	Subject& operator=(Subject&& other) = delete;

	void AddObserver(Observer* pObserver);
	void RemoveObserver(Observer* pObserver);
	void Notify(GameObject* pGameObject, const GameEvent& event);

protected:
	std::vector<Observer*> m_pObservers;
};
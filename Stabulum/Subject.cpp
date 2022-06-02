#include "StabulumPCH.h"
#include "Subject.h"

void Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Subject::RemoveObserver(Observer* pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver));
}

void Subject::Notify(GameObject* pGameObject, const GameEvent& event)
{
	for (Observer* pObserver : m_pObservers)
	{
		pObserver->OnNotify(pGameObject, event);
	}
}
#pragma once

#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent() = default;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Update() = 0;
	virtual void FixedUpdate();
	virtual void Render() const;

	void SetGameObject(GameObject* pGameObject) { m_pGameObject = pGameObject; }
	GameObject* GetGameObject() { return m_pGameObject; }

protected:
	GameObject* m_pGameObject;
};
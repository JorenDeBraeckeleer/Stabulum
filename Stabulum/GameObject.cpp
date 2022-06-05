#include "StabulumPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

GameObject::GameObject()
	: m_pComponents{}
	, m_pParentObject{}
	, m_pChildren{}
{
}

GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
}

void GameObject::Update()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update();
	}

	for (GameObject* pObj : m_pChildren)
	{
		pObj->Update();
	}
}

void GameObject::FixedUpdate()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->FixedUpdate();
	}

	for (GameObject* pObj : m_pChildren)
	{
		pObj->FixedUpdate();
	}
}

void GameObject::Render() const
{
	for (BaseComponent* pComp : m_pComponents)
	{
		if (dynamic_cast<RenderComponent*>(pComp))
		{
			pComp->Render();
		}
	}

	for (GameObject* pObj : m_pChildren)
	{
		pObj->Render();
	}
}

void GameObject::SetParent(GameObject* pGameObject)
{
	//Integrity check
	if (pGameObject == this || this->m_pParentObject == pGameObject)
	{
		return;
	}

	//Remove child from old parent if it had one
	if (this->m_pParentObject)
	{
		this->m_pParentObject->RemoveChild(this, false);
	}

	//Add as child
	pGameObject->AddChild(this);
}

void GameObject::AddChild(GameObject* pGameObject)
{
	//Integrity check
	if (pGameObject == this || pGameObject->m_pParentObject == this)
	{
		return;
	}

	//Remove child from old parent if it had one
	if (pGameObject->m_pParentObject)
	{
		pGameObject->m_pParentObject->RemoveChild(pGameObject, false);
	}

	//Set new parent
	pGameObject->m_pParentObject = this;

	//Add to children
	m_pChildren.push_back(pGameObject);

	//Set relative transform for child
	TransformComponent* transformCompParent{ this->GetComponent<TransformComponent>() };
	TransformComponent* transformCompChild{ pGameObject->GetComponent<TransformComponent>() };
	if (transformCompParent && transformCompChild)
	{
		FVec2 transform{ transformCompParent->GetWorldPosition() + transformCompChild->GetLocalPosition() };
		transformCompChild->SetWorldPosition(transform);
	}
}

void GameObject::RemoveChild(GameObject* pGameObject, bool deleteGameObject)
{
	//Find game object
	auto it{ std::remove(m_pChildren.begin(), m_pChildren.end(), pGameObject) };

	//If it exists
	if (it != m_pChildren.end())
	{
		//Remove
		m_pChildren.erase(it);

		//De-parent
		pGameObject->m_pParentObject = nullptr;

		//Delete if wanted
		if (deleteGameObject)
		{
			delete pGameObject;
			pGameObject = nullptr;
		}
	}
}
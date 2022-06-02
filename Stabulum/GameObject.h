#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <type_traits>

class BaseComponent;
class Texture2D;

class GameObject final : public SceneObject
{
public:
	GameObject();

	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	GameObject* GetParent() { return m_pParentObject; }
	void SetParent(GameObject* pGameObject);
	void AddChild(GameObject* pGameObject);
	void RemoveChild(GameObject* pGameObject, bool deleteGameObject = true);

	//Maximum of 1 component per type, gives back the old component if one already exists.
	template <typename myType, typename... myArgs>
	myType* AddComponent(myArgs&&... args)
	{
		//Search for already existing component so we don't make a duplicate
		myType* pComp{};

		for (size_t idx{}; idx < m_pComponents.size() && !pComp; ++idx)
		{
			pComp = dynamic_cast<myType*>(m_pComponents[idx]);
		}

		if (pComp)
		{
			return pComp;
		}

		//Make new component
		myType* pComponent = new myType(args...);
		pComponent->SetGameObject(this);
		m_pComponents.push_back(pComponent);

		return pComponent;
	}

	template<typename myType>
	myType* GetComponent() const
	{
		//Search for existing component
		myType* pComp{};

		for (size_t idx{}; idx < m_pComponents.size() && !pComp; ++idx)
		{
			pComp = dynamic_cast<myType*>(m_pComponents[idx]);
		}

		return pComp;
	};

	template <typename myType>
	void RemoveComponent()
	{
		//Search for existing component
		myType* pComp{};

		for (size_t idx{}; idx < m_pComponents.size() && !pComp; ++idx)
		{
			pComp = dynamic_cast<myType*>(m_pComponents[idx]);
		}

		//Delete found component
		if (pComp)
		{
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComp));

			pComp->SetGameObject(nullptr);

			//Signal parent of lost child
			//...

			delete pComp;
			pComp = nullptr;
		}
	}

private:
	std::vector<BaseComponent*> m_pComponents;

	GameObject* m_pParentObject;
	std::vector<GameObject*> m_pChildren;
};
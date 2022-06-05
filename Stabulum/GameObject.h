#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <type_traits>
#include <typeinfo>

class BaseComponent;
class RigidBodyComponent;
class ColliderComponent;
class Texture2D;
class Scene;

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
	std::vector<GameObject*> GetChildren() { return m_pChildren; }
	void AddChild(GameObject* pGameObject);
	void RemoveChild(GameObject* pGameObject, bool deleteGameObject = true);

	void SetScene(Scene* pScene);
	Scene* GetScene() const;

	//Maximum of 1 component per type, gives back the old component if one already exists.
	//Exception for Collider components
	template <typename myType, typename... myArgs>
	myType* AddComponent(myArgs&&... args)
	{
		//Search for already existing component so we don't make a duplicate
		myType* pComp{};

		for (size_t idx{}; idx < m_pComponents.size() && !pComp; ++idx)
		{
			pComp = dynamic_cast<myType*>(m_pComponents[idx]);
		}

		if (pComp && !std::is_base_of_v<ColliderComponent, myType>)
		{
			return pComp;
		}

		//Make new component
		myType* pComponent = new myType(args...);
		pComponent->SetGameObject(this);
		m_pComponents.push_back(pComponent);

		return pComponent;
	}

	////Not tested yet
	//template<typename myType>
	//myType* GetComponentInChildren() const
	//{
	//	//Search for existing component
	//	myType* pComp{};

	//	for (size_t idx{}; idx < m_pChildren.size() && !pComp; ++idx)
	//	{
	//		pComp = dynamic_cast<myType*>(m_pChildren[idx]->GetComponent<myType>());
	//	}

	//	return pComp;
	//};

	//Not tested yet
	template<typename myType>
	myType* GetComponentInParents() const
	{
		//Search for existing component
		if (myType* pComp = GetComponent<myType>())
		{
			return pComp;
		}

		if (m_pParentObject)
		{
			return m_pParentObject->GetComponentInParents<myType>();
		}

		return nullptr;
	};

	template<typename myType>
	myType* GetComponent() const
	{
		//Search for existing component
		myType* pComp{ nullptr };

		for (size_t idx{}; idx < m_pComponents.size() && !pComp; ++idx)
		{
			pComp = dynamic_cast<myType*>(m_pComponents[idx]);
		}

		return pComp;
	};

	template<typename myType>
	std::vector<myType*> GetComponents() const
	{
		//Search for existing component
		std::vector<myType*> pComponents{};

		for (BaseComponent* pC : m_pComponents)
		{
			if (myType* pComp = dynamic_cast<myType*>(pC))
			{
				pComponents.emplace_back(pComp);
			}
		}

		return pComponents;
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

	Scene* m_pScene;
};
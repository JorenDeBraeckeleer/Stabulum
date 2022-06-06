#pragma once

#include "GameObject.h"
#include "SceneManager.h"

class SceneObject;

class Scene final
{
	friend Scene& SceneManager::CreateScene(const std::string& name);

public:
	void Add(const std::shared_ptr<SceneObject>& object);

	void Update();
	void FixedUpdate();
	void Render() const;

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	template<typename myType>
	myType* FindComponent() const
	{
		//Search for existing component
		myType* pComp{ nullptr };

		for (size_t idx{}; idx < m_Objects.size() && !pComp; ++idx)
		{
			if (GameObject* pGameObject = dynamic_cast<GameObject*>(m_Objects[idx].get()))
			{
				pComp = pGameObject->GetComponent<myType>();
			}
		}

		return pComp;
	}

	template<typename myType>
	std::vector<myType*> FindComponents() const
	{
		//Search for existing component
		std::vector<myType*> pComponents{};

		for (std::shared_ptr<SceneObject> pObj : m_Objects)
		{
			if (GameObject* pGameObject = dynamic_cast<GameObject*>(pObj.get()))
			{
				std::vector<myType*> pComps = pGameObject->GetComponents<myType>();
				pComponents.insert(pComponents.end(), pComps.begin(), pComps.end());
			}
		}

		return pComponents;
	}

private: 
	explicit Scene(const std::string& name);

	const std::string m_Name;
	std::vector <std::shared_ptr<SceneObject>> m_Objects{};

	static unsigned int m_IdCounter; 
};
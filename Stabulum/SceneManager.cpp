#include "StabulumPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::FixedUpdate(float)
{
	for (const auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}

void SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
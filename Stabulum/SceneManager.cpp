#include "StabulumPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::FixedUpdate(float)
{
	if (m_pActiveScene)
	{
		m_pActiveScene->FixedUpdate();
	}
}

void SceneManager::Update()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->Update();
	}
}

void SceneManager::Render()
{
	if (m_pActiveScene)
	{
		m_pActiveScene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));

	if (int(m_Scenes.size()) == m_ActiveSceneIndex)
	{
		m_pActiveScene = scene.get();
	}

	m_Scenes.emplace_back(scene);
	return *scene;
}

void SceneManager::LoadNextScene()
{
	++m_ActiveSceneIndex;

	if (m_ActiveSceneIndex > int(m_Scenes.size()) - 1)
	{
		m_ActiveSceneIndex = 0;
	}
	if (m_ActiveSceneIndex < 0)
	{
		m_ActiveSceneIndex = int(m_Scenes.size()) - 1;
	}

	m_pActiveScene = m_Scenes[m_ActiveSceneIndex].get();
}

void SceneManager::LoadPreviousScene()
{
	--m_ActiveSceneIndex;

	if (m_ActiveSceneIndex > int(m_Scenes.size()) - 1)
	{
		m_ActiveSceneIndex = 0;
	}
	if (m_ActiveSceneIndex < 0)
	{
		m_ActiveSceneIndex = int(m_Scenes.size()) - 1;
	}

	m_pActiveScene = m_Scenes[m_ActiveSceneIndex].get();
}
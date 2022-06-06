#pragma once

#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	virtual ~SceneManager() override = default;
	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) noexcept = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) noexcept = delete;

	Scene& CreateScene(const std::string& name);

	void FixedUpdate(float fixedDeltaTime);
	void Update();
	void Render();

	Scene* GetActiveScene() { return m_pActiveScene; }

	void LoadNextScene();
	void LoadPreviousScene();

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes;

	Scene* m_pActiveScene = nullptr;
	int m_ActiveSceneIndex = 0;
	bool m_IsFirstTick = true;
};
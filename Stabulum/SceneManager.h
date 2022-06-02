#pragma once
#include "Singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);

	void FixedUpdate(float fixedDeltaTime);
	void Update();
	void Render();

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes;
};
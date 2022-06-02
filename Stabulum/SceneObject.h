#pragma once

class SceneObject
{
public:
	SceneObject() = default;

	virtual ~SceneObject() = default;
	SceneObject(const SceneObject& other) = delete;
	SceneObject(SceneObject&& other) = delete;
	SceneObject& operator=(const SceneObject& other) = delete;
	SceneObject& operator=(SceneObject&& other) = delete;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render() const = 0;

private:
};
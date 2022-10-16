#pragma once

#include <Windows.h>

class Scene;

class SceneManager
{
private:
	// ΩÃ±€≈Ê
	static std::shared_ptr<SceneManager> instance_;
	static std::once_flag flag_;

	std::shared_ptr<Scene> scenes_[(size_t)SceneType::kEnd];
	std::shared_ptr<Scene> current_scene_;
public:
	SceneManager();
	~SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	static std::shared_ptr<SceneManager> GetInstance();

	void Release();

	void Initiate();
	void Update(float delta_time);
	void LateUpdate(float delta_time);
	void Render(HDC hdc);
	std::shared_ptr<Scene> GetCurrentScene();
};


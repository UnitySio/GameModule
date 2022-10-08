#pragma once

#include "framework.h"

class Scene;

enum class SceneType
{
	kTEST = 0,
	kDUMMY // 실제로는 사용되지 않는 Scene 타입
};

class SceneManager
{
private:
	// 싱글톤
	static unique_ptr<SceneManager> instance_;
	static once_flag flag_;

	shared_ptr<Scene> scenes_[(size_t)SceneType::kDUMMY];
	shared_ptr<Scene> current_scene_;
public:
	SceneManager() = default;
	~SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	static SceneManager* GetInstance();

	void Initiate();
	void Update(float delta_time);
	void LateUpdate(float delta_time);
	void Render(HDC hdc);
};


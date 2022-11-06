#pragma once

// Å¬·¡½º Àü¹æ ¼±¾ð
class Scene;
class Object;

class SceneManager
{
private:
	// ½Ì±ÛÅæ
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
	void CreateScene(std::shared_ptr<Scene> scene, SceneType scene_type, LPCWSTR name);
	void LoadScene(SceneType scene_type);
	void InputUpdate();
	void Update();
	void LateUpdate();
	void PhysicsUpdate();
	void Render();
	void ObjectUpdate();
	void Destroy(Object* object);

	std::shared_ptr<Scene> GetCurrentScene();
};

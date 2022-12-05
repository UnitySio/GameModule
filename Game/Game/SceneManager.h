#pragma once

#include "Singleton.h"

// 클래스 전방 선언
class Scene;
class Object;

class SceneManager :
    public Singleton<SceneManager>
{
private:
    struct ObjectInfo
    {
        std::shared_ptr<Object> object;
        LayerType type;
        LPCWSTR name;
        Vector2 position;
        Vector2 scale;
    };

    std::shared_ptr<Scene> scenes_[(size_t)SceneType::kEnd];
    std::shared_ptr<Scene> current_scene_;

    std::vector<ObjectInfo> objects_;
public:
    SceneManager();
    ~SceneManager() final = default;

    void Initiate();
    void CreateScene(std::shared_ptr<Scene> scene, SceneType scene_type, LPCWSTR kName);
    void LoadScene(SceneType scene_type);
    void Update();
    void LateUpdate();
    void PhysicsUpdate();
    void Render();
    void SceneUpdate();
    void Instantiate(std::shared_ptr<Object> object, LayerType type, LPCWSTR kName, Vector2 position, Vector2 scale);
    void Destroy(std::shared_ptr<Object> object);

    std::shared_ptr<Scene> GetCurrentScene();
};

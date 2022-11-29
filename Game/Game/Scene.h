#pragma once

class Object;

class Scene
{
private:
    friend class SceneManager;

    WCHAR name_[128];

    std::vector<std::shared_ptr<Object>> objects_[(size_t)LayerType::kEnd];
public:
    Scene();
    virtual ~Scene() = default; // 자식 클래스의 소멸자를 호출하기 위해 virtual로 선언

    void SetName(LPCWSTR kName);
    void CreateObject(std::shared_ptr<Object> object, LayerType type, LPCWSTR kName, Vector2 position, Vector2 scale);
    void SceneUpdate();

    std::shared_ptr<Object> FindObject(LPCWSTR kName);

    LPCWSTR GetName();

    // 추상 함수
    virtual void Enter() = 0;

    // 가상 함수
    virtual void Exit();
    virtual void Update();
    virtual void LateUpdate();
    virtual void PhysicsUpdate();
    virtual void Render();

    const std::vector<std::shared_ptr<Object>>& GetLayerObjects(LayerType type);
};

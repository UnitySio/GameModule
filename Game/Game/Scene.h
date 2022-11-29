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
    virtual ~Scene() = default; // �ڽ� Ŭ������ �Ҹ��ڸ� ȣ���ϱ� ���� virtual�� ����

    void SetName(LPCWSTR kName);
    void CreateObject(std::shared_ptr<Object> object, LayerType type, LPCWSTR kName, Vector2 position, Vector2 scale);
    void SceneUpdate();

    std::shared_ptr<Object> FindObject(LPCWSTR kName);

    LPCWSTR GetName();

    // �߻� �Լ�
    virtual void Enter() = 0;

    // ���� �Լ�
    virtual void Exit();
    virtual void Update();
    virtual void LateUpdate();
    virtual void PhysicsUpdate();
    virtual void Render();

    const std::vector<std::shared_ptr<Object>>& GetLayerObjects(LayerType type);
};

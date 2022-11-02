#pragma once

class Object;

class Scene
{
private:
	friend class SceneManager;

	WCHAR name_[128];

	std::list<std::shared_ptr<Object>> objects_[(size_t)LayerType::kEnd];
public:
	Scene();
	virtual ~Scene() = default; // �ڽ� Ŭ������ �Ҹ��ڸ� ȣ���ϱ� ���� virtual�� ����

	void SetName(LPCWSTR name);
	void CreateObject(std::shared_ptr<Object> object, LayerType type, LPCWSTR name, Vector2 position, Vector2 rotation, Vector2 scale);

	LPCWSTR GetName();

	// �߻� �Լ�
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	// ���� �Լ�
	virtual void InputUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void PhysicsUpdate();
	virtual void Render();

	const std::list<std::shared_ptr<Object>>& GetLayerObjects(LayerType type);
};

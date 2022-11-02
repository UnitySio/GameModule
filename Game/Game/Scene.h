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
	virtual ~Scene() = default; // 자식 클래스의 소멸자를 호출하기 위해 virtual로 선언

	void SetName(LPCWSTR name);
	void CreateObject(std::shared_ptr<Object> object, LayerType type, LPCWSTR name, Vector2 position, Vector2 rotation, Vector2 scale);

	LPCWSTR GetName();

	// 추상 함수
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	// 가상 함수
	virtual void InputUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void PhysicsUpdate();
	virtual void Render();

	const std::list<std::shared_ptr<Object>>& GetLayerObjects(LayerType type);
};

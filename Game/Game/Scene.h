#pragma once

class Object;

class Scene
{
private:
	WCHAR name_[1024];
	//std::vector<std::shared_ptr<Layer>> layers_;
	std::vector<std::shared_ptr<Object>> objects_[(size_t)LayerType::kEND];
public:
	Scene();
	virtual ~Scene() = default;

	void SetName(LPCWSTR name);
	LPCWSTR GetName();

	//std::shared_ptr<Layer> CreateLayer(LPCWSTR name, UINT z_order);

	virtual void Update(float delta_time);
	virtual void LateUpdate(float delta_time);
	virtual void Render(HDC hdc);

	void CreateObject(std::shared_ptr<Object> object, LayerType type);

	const std::vector<std::shared_ptr<Object>>& GetGroupObject(LayerType type);
	
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

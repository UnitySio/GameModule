#pragma once

class Layer;
class Object;

class Scene
{
private:
	WCHAR name_[1024];
	std::vector<std::shared_ptr<Layer>> layers_;
public:
	Scene();
	virtual ~Scene() = default;

	void SetName(LPCWSTR name);
	LPCWSTR GetName();

	std::shared_ptr<Layer> CreateLayer(LPCWSTR name, UINT z_order);
	
	virtual void Update(float delta_time);
	virtual void LateUpdate(float delta_time);
	virtual void Render(HDC hdc);

	const std::vector<std::shared_ptr<Object>>& GetGroupObject(GroupObjectType type);

	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

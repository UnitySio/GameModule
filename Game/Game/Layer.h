#pragma once

class Object;

class Layer
{
private:
	friend class Scene;

	WCHAR name_[1024];
	UINT z_order_;
	std::vector<std::shared_ptr<Object>> objects_[(size_t)GroupObjectType::kEND];
public:
	Layer();
	~Layer() = default;

	void SetName(LPCWSTR name);
	void SetZOrder(UINT z_order);

	void Update(float delta_time);
	void LateUpdate(float delta_time);
	void Render(HDC hdc);

	LPCWSTR GetName();
	UINT GetZOrder();

	void CreateObject(std::shared_ptr<Object> object, GroupObjectType type);
	std::shared_ptr<Object> FindObject(LPCWSTR name);
	void DestroyObject(std::shared_ptr<Object> object);
};

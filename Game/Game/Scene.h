#pragma once

#include "Window.h"
#include "Object.h"

using namespace std;
#include <vector>

enum class ObjectTypeGroup
{
	kDEFAULT = 0,
	kPLAYER,
	kDUMMY // 실제로는 사용되지 않는 Object 타입
};

class Scene
{
private:
	WCHAR name_[1024];
	vector<shared_ptr<Object>> objects_[(size_t)ObjectTypeGroup::kDUMMY];
public:
	Scene() = default;
	virtual ~Scene() = default;

	void SetName(LPCWSTR name);
	LPCWSTR GetName();

	void CreateInstance(shared_ptr<Object> object, ObjectTypeGroup type);

	virtual void Update(float delta_time);
	virtual void LateUpdate(float delta_time);
	virtual void Render(HDC hdc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;
};


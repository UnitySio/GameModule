#pragma once

#include <Windows.h>

class Object
{
private:
	WCHAR name_[1024];
	Vector2 position_;
	Vector2 scale_;
	Vector2 pivot_;
public:
	Object();
	virtual ~Object() = default;

	virtual void Update(float delta_time) = 0;
	virtual void LateUpdate(float delta_time) = 0;
	virtual void Render(HDC hdc) = 0;

	void SetName(LPCWSTR name);
	void SetPosition(Vector2 position);
	void SetScale(Vector2 scale);
	void SetPivot(Vector2 pivot);
	void Translate(Vector2 vector2);
	
	LPCWSTR GetName();
	Vector2 GetPosition();
	Vector2 GetScale();
	Vector2 GetPivot();
	Vector2 GetRenderPositon();
};

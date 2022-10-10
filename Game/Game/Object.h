#pragma once

#include <Windows.h>

class Object
{
private:
	WCHAR name_[1024];
	Vector2 position_;
	Vector2 scale_;
public:
	Object();
	virtual ~Object() = default;

	virtual void Update(float delta_time) = 0;
	virtual void LateUpdate(float delta_time) = 0;
	virtual void Render(HDC hdc) = 0;

	void SetName(LPCWSTR name);
	void SetPosition(Vector2 position_);
	void SetScale(Vector2 scale_);
	
	LPCWSTR GetName();
	Vector2 GetPosition();
	Vector2 GetScale();
};

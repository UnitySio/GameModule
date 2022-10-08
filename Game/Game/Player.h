#pragma once

#include "Object.h"
#define GetKeyDown(virtual_key) (GetAsyncKeyState(virtual_key) & 0x8000)

class Player : public Object
{
private:
public:
	Player() = default;
	~Player() = default;

	virtual void Update(float delta_time);
	virtual void LateUpdate(float delta_time);
	virtual void Render(HDC hdc);
};


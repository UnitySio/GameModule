#pragma once

#include "Object.h"

class Block : public Object
{
private:
public:
	Block();
	~Block() final = default;

	void Update(float delta_time) final;
	void LateUpdate(float delta_time) final;
	void Render(HDC hdc) final;
};


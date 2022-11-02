#pragma once

#include "Object.h"

class GroundObject : public Object
{
private:
public:
	GroundObject();
	~GroundObject() final = default;

	void Render();
};


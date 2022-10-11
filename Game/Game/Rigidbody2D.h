#pragma once

#include "Object.h"

class Rigidbody2D
{
private:
	std::shared_ptr<Object> owner_;
	float mass_; // ����
public:
	Rigidbody2D() = default;
	~Rigidbody2D() = default;
};


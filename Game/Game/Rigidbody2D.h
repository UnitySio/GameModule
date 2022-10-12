#pragma once

#include "Object.h"

class Rigidbody2D
{
private:
	friend class Object;

	Object* owner_;

	float mass_; // 질량

	Vector2 force_; // 힘
	Vector2 acceleration_; // 가속도
	Vector2 velocity_; // 속도
	Vector2 friction_; // 마찰
public:
	Rigidbody2D();
	~Rigidbody2D() = default;

	void LateUpdate(float delta_time);

	void AddForce(Vector2 force);
};


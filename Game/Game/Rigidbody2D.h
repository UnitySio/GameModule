#pragma once

class Object;

class Rigidbody2D
{
private:
	friend class Object;

	Object* owner_;

	Vector2 force_; // 힘
	float mass_; // 질량
	float friction_coefficient_; // 마찰 계수
	float max_speed_; // 최대 속도

	Vector2 acceleration_; // 가속도
	Vector2 velocity_; // 속도
	Vector2 friction_; // 마찰
public:
	Rigidbody2D();
	Rigidbody2D(const Rigidbody2D& kOrigin);
	~Rigidbody2D() = default;

	Rigidbody2D& operator=(Rigidbody2D&) = delete;

	void LateUpdate(float delta_time);

	void AddForce(Vector2 force);
	void SetForce(Vector2 force);

	Vector2 GetVelocity();
};


#pragma once

class Object;

class Rigidbody2D
{
private:
	friend class Object;

	Object* owner_;

	Vector2 force_; // 힘
	Vector2 acceleration_; // 가속도
	Vector2 gravity_acceleration_; // 중력 가속도
	Vector2 friction_; // 마찰력
	Vector2 velocity_; // 속도

	float mass_; // 질량
	float friction_coefficient_; // 마찰 계수
	float drag_; // 항력 계수
public:
	Rigidbody2D();
	Rigidbody2D(const Rigidbody2D& kOrigin);
	~Rigidbody2D() = default;

	Rigidbody2D& operator=(const Rigidbody2D&) = delete;

	void SetVelocity(Vector2 velocity);
	void AddForce(Vector2 force);
	void SetMass(float mass);
	void SetFrictionCoefficient(float friction_coefficient);
	void SetDrag(float drag);
	void SetGravityAcceleration(Vector2 acceleration);
	void PhysicsUpdate();

	Vector2 GetVelocity();
};

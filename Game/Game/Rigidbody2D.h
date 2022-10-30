#pragma once

class Object;

class Rigidbody2D
{
private:
	friend class Object;

	Object* owner_;

	Vector2 velocity_;
public:
	Rigidbody2D();
	Rigidbody2D(const Rigidbody2D& kOrigin);
	~Rigidbody2D() = default;

	void SetVelocity(Vector2 velocity);
	void PhysicsUpdate();

	Vector2 GetVelocity();
};


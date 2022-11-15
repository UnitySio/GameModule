#pragma once

class Object;

class Rigidbody2D
{
private:
	friend class Object;

	Object* owner_;

	Vector2 force_; // ��
	Vector2 acceleration_; // ���ӵ�
	Vector2 gravity_acceleration_; // �߷� ���ӵ�
	Vector2 friction_; // ������
	Vector2 velocity_; // �ӵ�

	float mass_; // ����
	float friction_coefficient_; // ���� ���
	float drag_; // �׷� ���
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

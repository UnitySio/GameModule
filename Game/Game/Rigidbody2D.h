#pragma once

class Object;

class Rigidbody2D
{
private:
	friend class Object;

	Object* owner_;

	Vector2 force_; // ��
	float mass_; // ����
	float friction_coefficient_; // ���� ���
	float max_speed_; // �ִ� �ӵ�

	Vector2 acceleration_; // ���ӵ�
	Vector2 velocity_; // �ӵ�
	Vector2 friction_; // ����
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


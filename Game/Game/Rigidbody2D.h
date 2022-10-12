#pragma once

#include "Object.h"

class Rigidbody2D
{
private:
	friend class Object;

	Object* owner_;

	float mass_; // ����

	Vector2 force_; // ��
	Vector2 acceleration_; // ���ӵ�
	Vector2 velocity_; // �ӵ�
	Vector2 friction_; // ����
public:
	Rigidbody2D();
	~Rigidbody2D() = default;

	void LateUpdate(float delta_time);

	void AddForce(Vector2 force);
};


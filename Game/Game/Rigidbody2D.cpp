#include "pch.h"
#include "Rigidbody2D.h"
#include "Object.h"

using namespace std;

Rigidbody2D::Rigidbody2D() : owner_(), mass_(1), friction_coefficient_(100), max_speed_(500), force_{}, acceleration_{}, velocity_{}
{
}

Rigidbody2D::Rigidbody2D(const Rigidbody2D& kOrigin) : owner_(), mass_(1), friction_coefficient_(100), max_speed_(500), force_{}, acceleration_{}, velocity_{}
{
}

void Rigidbody2D::LateUpdate(float delta_time)
{
	// F = m * a (�� = ���� * ���ӵ�)
	// A = f / m (���ӵ� = �� / ����)
	acceleration_ = force_ / mass_;
	velocity_ += acceleration_ * delta_time;

	// F = �� * N (������ = ���� ��� * �����׷�)
	if (velocity_ != Vector2().Zero())
	{
		// ���� ������ ������ �ݴ� ����
		Vector2 friction_direction = velocity_ * -1;

		friction_ = friction_direction.Normalized() * friction_coefficient_ * delta_time;

		velocity_ += friction_;
	}

	// �ӵ� ����
	if (velocity_.Magnitude() > max_speed_)
	{
		velocity_ = velocity_.Normalized() * max_speed_;
	}

	// ������Ʈ���� ����
	owner_->Translate(velocity_ * delta_time);

	// ������ �� �ʱ�ȭ
	force_ = Vector2().Zero();
}

void Rigidbody2D::AddForce(Vector2 force)
{
	force_ += force; // �� ����
}

void Rigidbody2D::SetForce(Vector2 force)
{
	force_ = force;
}

Vector2 Rigidbody2D::GetVelocity()
{
	return velocity_;
}

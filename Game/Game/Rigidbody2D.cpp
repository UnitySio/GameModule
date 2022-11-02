#include "pch.h"
#include "Rigidbody2D.h"
#include "Object.h"
#include "Window.h"

Rigidbody2D::Rigidbody2D() :
	owner_(),
	force_{},
	acceleration_{},
	friction_{},
	velocity_{},
	mass_(1),
	friction_coefficient_(100),
	drag_()
{
}

Rigidbody2D::Rigidbody2D(const Rigidbody2D& kOrigin) :
	owner_(),
	force_{},
	acceleration_{},
	friction_{},
	velocity_{},
	mass_(kOrigin.mass_),
	friction_coefficient_(kOrigin.friction_coefficient_),
	drag_(kOrigin.drag_)
{
}

void Rigidbody2D::SetVelocity(Vector2 velocity)
{
	velocity_ = velocity;
}

void Rigidbody2D::AddForce(Vector2 force)
{
	force_ += force;
}

void Rigidbody2D::SetGravityAcceleration(Vector2 acceleration)
{
	gravity_acceleration_ = acceleration;
}

void Rigidbody2D::PhysicsUpdate()
{
	// F = m * a (�� = ���� * ���ӵ�)
	// A = f / m (���ӵ� = �� / ����)
	acceleration_ = force_ / mass_;
	acceleration_ += gravity_acceleration_; // �߷� ���ӵ�
	velocity_ += acceleration_ * DELTA_TIME;

	// F = �� * N (������ = ���� ��� * ���� �׷�)
	if (velocity_ != Vector2().Zero())
	{
		// ������ ����
		Vector2 friction_direction = velocity_ * -1;

		friction_ = friction_direction.Normalized() * friction_coefficient_ * DELTA_TIME;
		velocity_ += friction_;

		/*if (velocity_.x_ < 0.01f)
		{
			velocity_.x_ = 0.f;
		}

		if (velocity_.y_ < 0.01f)
		{
			velocity_.y_ = 0.f;
		}*/
	}

	// V = V * (1 - D * dt) (���׷�)
	//velocity_ = velocity_ * (1 - drag_ * DELTA_TIME);

	owner_->Translate(velocity_ * DELTA_TIME);


	// Linear Sleep Tolerance
	/*if (velocity_.x_ < 0.01f)
	{
		velocity_.x_ = 0.f;
	}

	if (velocity_.y_ < 0.01f)
	{
		velocity_.y_ = 0.f;
	}*/

	// ������ �� �ʱ�ȭ
	force_ = Vector2().Zero();
	acceleration_ = Vector2().Zero();
	gravity_acceleration_ = Vector2().Zero();

	/*WCHAR word[128];
	_stprintf_s(word, L"X: %f, Y: %f\n", velocity_.x_, velocity_.y_);
	OutputDebugString(word);*/
}

Vector2 Rigidbody2D::GetVelocity()
{
	return velocity_;
}

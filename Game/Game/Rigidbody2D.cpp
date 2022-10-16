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
	// F = m * a (힘 = 질량 * 가속도)
	// A = f / m (가속도 = 힘 / 질량)
	acceleration_ = force_ / mass_;
	velocity_ += acceleration_ * delta_time;

	// F = μ * N (마찰력 = 마찰 계수 * 수직항력)
	if (velocity_ != Vector2().Zero())
	{
		// 힘이 가해진 방향의 반대 방향
		Vector2 friction_direction = velocity_ * -1;

		friction_ = friction_direction.Normalized() * friction_coefficient_ * delta_time;

		velocity_ += friction_;
	}

	// 속도 제한
	if (velocity_.Magnitude() > max_speed_)
	{
		velocity_ = velocity_.Normalized() * max_speed_;
	}

	// 오브젝트에게 적용
	owner_->Translate(velocity_ * delta_time);

	// 누적된 힘 초기화
	force_ = Vector2().Zero();
}

void Rigidbody2D::AddForce(Vector2 force)
{
	force_ += force; // 힘 누적
}

void Rigidbody2D::SetForce(Vector2 force)
{
	force_ = force;
}

Vector2 Rigidbody2D::GetVelocity()
{
	return velocity_;
}

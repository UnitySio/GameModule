#include "pch.h"
#include "Rigidbody2D.h"

using namespace std;

Rigidbody2D::Rigidbody2D() : owner_(), mass_(1), force_{}, acceleration_{}, velocity_{}
{
}

void Rigidbody2D::LateUpdate(float delta_time)
{
	// F = m * a (힘 = 질량 * 가속도)
	// A = f / m (가속도 = 힘 / 질량)
	acceleration_ = force_ / mass_;
	velocity_ += acceleration_ * delta_time;

	// 마찰력
	/*if (velocity_ != Vector2().Zero())
	{
		// 힘이 가해진 방향의 반대 방향
		Vector2 friction_direction = velocity_ * -1;

		friction_ = friction_direction.Normalized() * 40 * delta_time;

		velocity_ += friction_;
	}*/

	// 오브젝트에게 적용
	Vector2 position = owner_->GetPosition();
	position += velocity_ * delta_time;

	owner_->SetPosition(position);

	// 누적된 힘 초기화
	force_ = Vector2().Zero();
}

void Rigidbody2D::AddForce(Vector2 force)
{
	force_ += force; // 힘 누적
}

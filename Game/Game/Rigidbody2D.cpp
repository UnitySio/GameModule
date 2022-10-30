#include "pch.h"
#include "Rigidbody2D.h"
#include "Object.h"

Rigidbody2D::Rigidbody2D() :
	owner_(),
	velocity_{}
{
}

Rigidbody2D::Rigidbody2D(const Rigidbody2D& kOrigin) :
	owner_(),
	velocity_{}
{
}

void Rigidbody2D::SetVelocity(Vector2 velocity)
{
	velocity_ = velocity;
}

void Rigidbody2D::PhysicsUpdate()
{
	// F = ¥ì * N (¸¶Âû·Â = ¸¶Âû °è¼ö * ¼öÁ÷ Ç×·Â)
	if (velocity_ != Vector2().Zero())
	{
		// ¸¶Âû·Â ¹æÇâ
		Vector2 friction_direction = velocity_ * -1;
	}

	owner_->Translate(velocity_ * DELTA_TIME);
}

Vector2 Rigidbody2D::GetVelocity()
{
	return velocity_;
}

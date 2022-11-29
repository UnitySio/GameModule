#include "pch.h"
#include "BossWalk.h"
#include "Animator.h"
#include "Rigidbody2D.h"

using namespace std;

BossWalk::BossWalk(Boss* owner) :
	owner_(owner)
{
}

void BossWalk::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"WALK");
}

void BossWalk::OnStateUpdate()
{
	shared_ptr<Object> target = owner_->target_;

	shared_ptr<Rigidbody2D> rigid = owner_->GetRigidbody2D();

	Vector2 position = owner_->GetPosition();

	// 타켓과의 거리
	float distance = Vector2().Distance(target->GetPosition(), owner_->GetPosition());

	if (target->GetPosition().x_ < position.x_ - 100)
	{
		owner_->direction_ = -1;
		rigid->SetVelocity({ -owner_->move_speed_, rigid->GetVelocity().y_ });
	}
	else if (target->GetPosition().x_ > position.x_ + 100)
	{
		owner_->direction_ = 1;
		rigid->SetVelocity({ owner_->move_speed_, rigid->GetVelocity().y_ });
	}

	if (distance < 100.f || distance > 300.f)
	{
		rigid->SetVelocity({ 0.f, rigid->GetVelocity().y_ });
		owner_->ChangeState(owner_->states_[(size_t)BossStateType::kIdle]);
	}
}

void BossWalk::OnStateExit()
{
}

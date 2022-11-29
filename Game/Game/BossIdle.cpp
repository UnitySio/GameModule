#include "pch.h"
#include "BossIdle.h"
#include "Animator.h"
#include "Player.h"

using namespace std;

BossIdle::BossIdle(Boss* owner) :
	owner_(owner)
{
}

void BossIdle::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"IDLE");
}

void BossIdle::OnStateUpdate()
{
	shared_ptr<Object> target = owner_->target_;

	// 타켓과의 거리
	float distance = Vector2().Distance(target->GetPosition(), owner_->GetPosition());

	if (!(*(Player*)target.get()).IsDeath())
	{
		if (distance > 100.f && distance < 300.f)
		{
			owner_->ChangeState(owner_->states_[(size_t)BossStateType::kWalk]);
		}

		if (distance < 100.f)
		{
			if (!(*(Player*)target.get()).IsDash())
			{
				owner_->ChangeState(owner_->states_[(size_t)BossStateType::kAttack]);
			}
		}
	}
}

void BossIdle::OnStateExit()
{
}

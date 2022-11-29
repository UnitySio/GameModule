#include "pch.h"
#include "BossIdle.h"
#include "Animator.h"

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

	// Ÿ�ϰ��� �Ÿ�
	float distance = Vector2().Distance(target->GetPosition(), owner_->GetPosition());

	if (distance > 100.f && distance < 300.f)
	{
		owner_->ChangeState(owner_->states_[(size_t)BossStateType::kWalk]);
	}

	if (distance < 100.f)
	{
		owner_->ChangeState(owner_->states_[(size_t)BossStateType::kAttack]);
	}
}

void BossIdle::OnStateExit()
{
}

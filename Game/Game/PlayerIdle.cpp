#include "pch.h"
#include "PlayerIdle.h"
#include "InputManager.h"
#include "Animator.h"
#include "Rigidbody2D.h"

PlayerIdle::PlayerIdle(Player* owner) :
	owner_(owner)
{
}

void PlayerIdle::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"IDLE");
}

void PlayerIdle::OnStateUpdate()
{
	owner_->Movement();

	// 입력된 값이 0이 아닌경우 상태를 바꿈
	if (owner_->horizontal_ != 0.f)
	{
		owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kWalk]);
	}
}

void PlayerIdle::OnStateExit()
{
}

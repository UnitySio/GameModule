#include "pch.h"
#include "PlayerIdle.h"
#include "Animator.h"
#include "InputManager.h"

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
	int* h = &owner_->horizontal_;

	owner_->Movement();

	if (INPUT->GetKey(ATTACK))
	{
		owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kAttack]);
	}
	
	if (*h != 0)
	{
		owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kWalk]);
	}
}

void PlayerIdle::OnStateExit()
{
}

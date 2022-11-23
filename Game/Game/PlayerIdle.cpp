#include "pch.h"
#include "PlayerIdle.h"
#include "Animator.h"

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
}

void PlayerIdle::OnStateExit()
{
}

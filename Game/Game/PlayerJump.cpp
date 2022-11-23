#include "pch.h"
#include "PlayerJump.h"
#include "Animator.h"

PlayerJump::PlayerJump(Player* owner) :
	owner_(owner)
{
}

void PlayerJump::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"JUMP");
}

void PlayerJump::OnStateUpdate()
{
	owner_->Movement();
}

void PlayerJump::OnStateExit()
{
}

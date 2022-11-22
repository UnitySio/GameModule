#include "pch.h"
#include "PlayerJump.h"
#include "InputManager.h"
#include "Animator.h"
#include "Rigidbody2D.h"

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

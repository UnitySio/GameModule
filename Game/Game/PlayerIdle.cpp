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
}

void PlayerIdle::OnStateExit()
{
}

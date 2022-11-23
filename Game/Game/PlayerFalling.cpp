#include "pch.h"
#include "PlayerFalling.h"
#include "Animator.h"

PlayerFalling::PlayerFalling(Player* owner) :
	owner_(owner)
{
}

void PlayerFalling::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"FALLING");
}

void PlayerFalling::OnStateUpdate()
{
	owner_->Movement();
}

void PlayerFalling::OnStateExit()
{
}

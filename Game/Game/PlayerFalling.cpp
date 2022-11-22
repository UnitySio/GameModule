#include "pch.h"
#include "PlayerFalling.h"
#include "InputManager.h"
#include "Animator.h"
#include "Rigidbody2D.h"

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

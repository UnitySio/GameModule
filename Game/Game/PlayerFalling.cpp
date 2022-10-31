#include "pch.h"
#include "PlayerFalling.h"
#include "InputManager.h"
#include "Animator.h"

PlayerFalling::PlayerFalling(Player* owner) :
	owner_(owner)
{
}

void PlayerFalling::Enter()
{
	if (owner_->GetAnimator() != nullptr)
	{
		owner_->GetAnimator()->SetClip((size_t)PlayerClipType::kFalling);
	}
}

void PlayerFalling::Update()
{
}

void PlayerFalling::Exit()
{
}

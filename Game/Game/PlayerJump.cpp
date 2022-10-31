#include "pch.h"
#include "PlayerJump.h"
#include "InputManager.h"
#include "Animator.h"

PlayerJump::PlayerJump(Player* owner) :
	owner_(owner)
{
}

void PlayerJump::Enter()
{
	if (owner_->GetAnimator() != nullptr)
	{
		owner_->GetAnimator()->SetClip((size_t)PlayerClipType::kJump);
	}
}

void PlayerJump::Update()
{
}

void PlayerJump::Exit()
{
}

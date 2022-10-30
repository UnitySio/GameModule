#include "pch.h"
#include "PlayerIdle.h"
#include "InputManager.h"
#include "Animator.h"

PlayerIdle::PlayerIdle(Player* owner) :
	owner_(owner)
{
}

void PlayerIdle::Enter()
{
	if (owner_->GetAnimator() != nullptr)
	{
		owner_->GetAnimator()->SetClip((size_t)PlayerClipType::kIdle);
	}
}

void PlayerIdle::Update()
{
}

void PlayerIdle::Exit()
{
}

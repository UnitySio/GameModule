#include "pch.h"
#include "PlayerAttack.h"
#include "InputManager.h"
#include "Animator.h"

PlayerAttack::PlayerAttack(Player* owner) :
	owner_(owner)
{
}

void PlayerAttack::Enter()
{
	if (owner_->GetAnimator() != nullptr)
	{
		owner_->GetAnimator()->SetClip((size_t)PlayerClipType::kAttack);
	}
}

void PlayerAttack::Update()
{
	if (!owner_->GetAnimator()->IsPlay())
	{
		owner_->is_attack_ = false;
	}
}

void PlayerAttack::Exit()
{
}

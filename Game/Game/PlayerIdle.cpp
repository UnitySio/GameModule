#include "pch.h"
#include "PlayerIdle.h"
#include "InputManager.h"
#include "Animator.h"
#include "Rigidbody2D.h"

PlayerIdle::PlayerIdle(Player* owner) :
    owner_(owner)
{
}

void PlayerIdle::Enter()
{
    if (owner_->GetAnimator() != nullptr)
    {
        owner_->GetAnimator()->SetClip(L"IDLE");
    }
}

void PlayerIdle::Update()
{
    owner_->GetRigidbody2D()->SetVelocity({ owner_->horizontal, owner_->GetRigidbody2D()->GetVelocity().y_ });
}

void PlayerIdle::Exit()
{
}

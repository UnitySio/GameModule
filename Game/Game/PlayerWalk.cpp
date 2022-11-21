#include "pch.h"
#include "PlayerWalk.h"
#include "InputManager.h"
#include "Animator.h"
#include "Rigidbody2D.h"

PlayerWalk::PlayerWalk(Player* owner) :
    owner_(owner)
{
}

void PlayerWalk::Enter()
{
    if (owner_->GetAnimator() != nullptr)
    {
        owner_->GetAnimator()->SetClip(L"WALK");
    }
}

void PlayerWalk::Update()
{
    owner_->GetRigidbody2D()->SetVelocity({ owner_->horizontal, owner_->GetRigidbody2D()->GetVelocity().y_ });
}

void PlayerWalk::Exit()
{
}

#include "pch.h"
#include "PlayerWalk.h"
#include "Animator.h"
#include "Rigidbody2D.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

using namespace std;

PlayerWalk::PlayerWalk(Player* owner) :
    owner_(owner)
{
}

void PlayerWalk::OnStateEnter()
{
    owner_->GetAnimator()->SetClip(L"WALK");
}

void PlayerWalk::OnStateUpdate()
{
    int* h = &owner_->horizontal_;
    shared_ptr<Rigidbody2D> rigid = owner_->GetRigidbody2D();
    shared_ptr<SpriteRenderer> sprite = owner_->GetSpriteRenderer();

    owner_->Movement();

    if (rigid->GetVelocity().x_ > 0.f)
    {
        owner_->direction_ = 1;
        sprite->SetTexture(owner_->right_);
    }
    else if (rigid->GetVelocity().x_ < 0.f)
    {
        owner_->direction_ = -1;
        sprite->SetTexture(owner_->left_);
    }

    if (INPUT->GetKeyDown(DASH))
    {
        owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kDash]);
    }

    if (*h == 0)
    {
        owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kIdle]);
    }
}

void PlayerWalk::OnStateExit()
{
}

#include "pch.h"
#include "PlayerWalk.h"
#include "InputManager.h"
#include "Animator.h"
#include "Rigidbody2D.h"
#include "SpriteRenderer.h"

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
    owner_->Movement();

    // 입력된 값이 0일 경우 상태를 바꿈
    if (owner_->horizontal_ == 0.f)
    {
        owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kIdle]);
    }
}

void PlayerWalk::OnStateExit()
{
}

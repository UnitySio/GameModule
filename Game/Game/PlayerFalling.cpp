#include "pch.h"
#include "PlayerFalling.h"
#include "Animator.h"

using namespace std;

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

    if (owner_->is_ground_)
    {
        owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kIdle]);
    }
}

void PlayerFalling::OnStateExit()
{
}

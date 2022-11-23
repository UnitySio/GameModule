#include "pch.h"
#include "PlayerWalk.h"
#include "Animator.h"

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
}

void PlayerWalk::OnStateExit()
{
}

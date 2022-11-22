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
}

void PlayerWalk::OnStateExit()
{
}

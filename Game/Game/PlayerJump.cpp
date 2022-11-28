#include "pch.h"
#include "PlayerJump.h"
#include "Animator.h"
#include "Rigidbody2D.h"

using namespace std;

PlayerJump::PlayerJump(Player* owner) :
    owner_(owner)
{
}

void PlayerJump::OnStateEnter()
{
    shared_ptr<Rigidbody2D> rigid = owner_->GetRigidbody2D();

    owner_->GetAnimator()->SetClip(L"JUMP");
    rigid->SetVelocity({rigid->GetVelocity().x_, -owner_->jump_force_});
}

void PlayerJump::OnStateUpdate()
{
    owner_->Movement();
}

void PlayerJump::OnStateExit()
{
}

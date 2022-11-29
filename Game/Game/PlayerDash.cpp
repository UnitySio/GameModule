#include "pch.h"
#include "PlayerDash.h"
#include "Animator.h"
#include "Rigidbody2D.h"

using namespace std;

PlayerDash::PlayerDash(Player* owner) :
    owner_(owner)
{
}

void PlayerDash::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"DASH");

    owner_->GetRigidbody2D()->SetVelocity({ owner_->direction_ * 800.f, owner_->GetRigidbody2D()->GetVelocity().y_ });

    owner_->is_dash_ = true;
}

void PlayerDash::OnStateUpdate()
{
	shared_ptr<Animator> anim = owner_->GetAnimator();
    
    // 현재 애니메이션의 재생이 완료가 되었다면
    if (anim->IsDone())
    {
    owner_->GetRigidbody2D()->SetVelocity({ 0.f, owner_->GetRigidbody2D()->GetVelocity().y_ });
        owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kIdle]);
    }
}

void PlayerDash::OnStateExit()
{
    owner_->is_dash_ = false;
}

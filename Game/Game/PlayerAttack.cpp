#include "pch.h"
#include "PlayerAttack.h"
#include "Animator.h"
#include "SceneManager.h"
#include "PlayerHitBox.h"

using namespace std;

PlayerAttack::PlayerAttack(Player* owner) :
    owner_(owner)
{
}

void PlayerAttack::OnStateEnter()
{
    owner_->GetAnimator()->SetClip(L"ATTACK");

    int direction = owner_->direction_;
    Vector2 position = owner_->GetPosition();
    Vector2 create_position = { position.x_ + (direction * 50.f), position.y_ - 50.f };

    hit_box = make_shared<PlayerHitBox>();
    SCENE->Instantiate(hit_box, LayerType::kPlayerHitBox, L"HitBox", create_position, {});
}

void PlayerAttack::OnStateUpdate()
{
    shared_ptr<Animator> anim = owner_->GetAnimator();

    // 현재 애니메이션의 재생이 완료가 되었다면
    if (anim->IsDone())
    {
        owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kIdle]);
    }
}

void PlayerAttack::OnStateExit()
{
    SCENE->Destroy(hit_box);
}

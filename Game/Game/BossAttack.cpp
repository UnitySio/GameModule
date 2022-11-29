#include "pch.h"
#include "BossAttack.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "SceneManager.h"
#include "BossHitBox.h"

using namespace std;

BossAttack::BossAttack(Boss* owner) :
	owner_(owner)
{
}

void BossAttack::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"ATTACK");
}

void BossAttack::OnStateUpdate()
{
	shared_ptr<Animator> anim = owner_->GetAnimator();
	shared_ptr<SpriteRenderer> sprite = owner_->GetSpriteRenderer();

	UINT current_frame = sprite->GetCurrentFrame();

	if (current_frame == 4)
	{
		CreateHitBox();
	}

	if (current_frame == 5)
	{
		DestroyHitBox();
	}

	// 현재 애니메이션의 재생이 완료가 되었다면
	if (anim->IsDone())
	{
		owner_->ChangeState(owner_->states_[(size_t)BossStateType::kIdle]);
	}
}

void BossAttack::OnStateExit()
{
}

void BossAttack::CreateHitBox()
{
	int direction = owner_->direction_;

	Vector2 position = owner_->GetPosition();
	Vector2 create_position = { position.x_ + (direction * 28.f), position.y_ - 90.f };

	if (hit_box == nullptr)
	{
		hit_box = make_shared<BossHitBox>();
		SCENE->Instantiate(hit_box, LayerType::kBossHitBox, L"HitBox", create_position, {});
	}
}

void BossAttack::DestroyHitBox()
{
	if (hit_box != nullptr)
	{
		SCENE->Destroy(hit_box);
		hit_box = nullptr;
	}
}

#include "pch.h"
#include "PlayerAttack.h"
#include "SpriteRenderer.h"
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
}

void PlayerAttack::OnStateUpdate()
{
	shared_ptr<Animator> anim = owner_->GetAnimator();
	shared_ptr<SpriteRenderer> sprite = owner_->GetSpriteRenderer();

	UINT current_frame = sprite->GetCurrentFrame();

	if (current_frame == 5)
	{
		CreateHitBox();
	}

	if (current_frame == 6)
	{
		DestroyHitBox();
	}

	if (current_frame == 9)
	{
		CreateHitBox();
	}

	if (current_frame == 10)
	{
		DestroyHitBox();
	}

	// 현재 애니메이션의 재생이 완료가 되었다면
	if (anim->IsDone())
	{
		owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kIdle]);
	}
}

void PlayerAttack::OnStateExit()
{
}

void PlayerAttack::CreateHitBox()
{
	int direction = owner_->direction_;

	Vector2 position = owner_->GetPosition();
	Vector2 create_position = { position.x_ + (direction * 28.f), position.y_ - 60.f };

	if (hit_box == nullptr)
	{
		hit_box = make_shared<PlayerHitBox>();
		SCENE->Instantiate(hit_box, LayerType::kPlayerHitBox, L"HitBox", create_position, {});
	}
}

void PlayerAttack::DestroyHitBox()
{
	if (hit_box != nullptr)
	{
		SCENE->Destroy(hit_box);
		hit_box = nullptr;
	}
}

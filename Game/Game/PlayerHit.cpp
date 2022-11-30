#include "pch.h"
#include "PlayerHit.h"
#include "Animator.h"
#include "Rigidbody2D.h"

using namespace std;

PlayerHit::PlayerHit(Player* owner) :
	owner_(owner)
{
}

void PlayerHit::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"HIT");
}

void PlayerHit::OnStateUpdate()
{
	shared_ptr<Animator> anim = owner_->GetAnimator();

	// ���� �ִϸ��̼��� ����� �Ϸᰡ �Ǿ��ٸ�
	if (anim->IsDone())
	{
		if (owner_->GetHP() > 0.f)
		{
			owner_->ChangeState(owner_->states_[(size_t)PlayerStateType::kIdle]);
		}
	}
}

void PlayerHit::OnStateExit()
{
}

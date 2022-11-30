#include "pch.h"
#include "BossHit.h"
#include "Animator.h"
#include "Rigidbody2D.h"

using namespace std;

BossHit::BossHit(Boss* owner) :
	owner_(owner)
{
}

void BossHit::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"HIT");
}

void BossHit::OnStateUpdate()
{
	shared_ptr<Animator> anim = owner_->GetAnimator();

	// ���� �ִϸ��̼��� ����� �Ϸᰡ �Ǿ��ٸ�
	if (anim->IsDone())
	{
		if (owner_->GetHP() > 0.f)
		{
			owner_->ChangeState(owner_->states_[(size_t)BossStateType::kIdle]);
		}
	}
}

void BossHit::OnStateExit()
{
}

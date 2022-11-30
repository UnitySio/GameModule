#include "pch.h"
#include "PlayerDeath.h"
#include "Animator.h"
#include "Rigidbody2D.h"

using namespace std;

PlayerDeath::PlayerDeath(Player* owner) :
	owner_(owner)
{
}

void PlayerDeath::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"DEATH");
	owner_->GetRigidbody2D()->SetVelocity({});
	TIME->SetTimeScale(.2f);
}

void PlayerDeath::OnStateUpdate()
{
	shared_ptr<Animator> anim = owner_->GetAnimator();

	// ���� �ִϸ��̼��� ����� �Ϸᰡ �Ǿ��ٸ�
	if (anim->IsDone())
	{
		if (TIME->GetTimeScale() != 1.f)
		{
			TIME->SetTimeScale(1.f);
		}
	}
}

void PlayerDeath::OnStateExit()
{
}

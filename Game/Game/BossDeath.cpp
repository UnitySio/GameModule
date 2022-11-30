#include "pch.h"
#include "BossDeath.h"
#include "Animator.h"
#include "Rigidbody2D.h"

using namespace std;

BossDeath::BossDeath(Boss* owner) :
	owner_(owner)
{
}

void BossDeath::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"DEATH");
	owner_->GetRigidbody2D()->SetVelocity({});
	TIME->SetTimeScale(.2f);
}

void BossDeath::OnStateUpdate()
{
	shared_ptr<Animator> anim = owner_->GetAnimator();

	// 현재 애니메이션의 재생이 완료가 되었다면
	if (anim->IsDone())
	{
		if (TIME->GetTimeScale() != 1.f)
		{
			TIME->SetTimeScale(1.f);
		}
	}
}

void BossDeath::OnStateExit()
{
}

#include "pch.h"
#include "BossDeath.h"
#include "Animator.h"

BossDeath::BossDeath(Boss* owner) :
	owner_(owner)
{
}

void BossDeath::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"DEATH");
}

void BossDeath::OnStateUpdate()
{
}

void BossDeath::OnStateExit()
{
}

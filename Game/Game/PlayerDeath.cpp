#include "pch.h"
#include "PlayerDeath.h"
#include "Animator.h"

PlayerDeath::PlayerDeath(Player* owner) :
	owner_(owner)
{
}

void PlayerDeath::OnStateEnter()
{
	owner_->GetAnimator()->SetClip(L"DEATH");
}

void PlayerDeath::OnStateUpdate()
{
}

void PlayerDeath::OnStateExit()
{
}

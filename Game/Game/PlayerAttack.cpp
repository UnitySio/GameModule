#include "pch.h"
#include "PlayerAttack.h"
#include "InputManager.h"

PlayerAttack::PlayerAttack(Player* owner)
{
	owner_ = owner;
}

void PlayerAttack::Enter()
{
	owner_->temp_->SetClip("ATTACK");
}

void PlayerAttack::Update()
{
	if (INPUT_MANAGER->GetKeyUp(MK_LBUTTON))
	{
		owner_->ChangeState(owner_->states_[0]);
	}
}

void PlayerAttack::Exit()
{
}

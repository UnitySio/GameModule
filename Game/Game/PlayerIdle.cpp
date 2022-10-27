#include "pch.h"
#include "PlayerIdle.h"
#include "InputManager.h"

PlayerIdle::PlayerIdle(Player* owner)
{
	owner_ = owner;
}

void PlayerIdle::Enter()
{
	owner_->temp_->SetClip("IDLE");
}

void PlayerIdle::Update()
{
	if (INPUT_MANAGER->GetKey('A') ||
		INPUT_MANAGER->GetKey('D') ||
		INPUT_MANAGER->GetKey('W') ||
		INPUT_MANAGER->GetKey('S'))
	{
		owner_->ChangeState(owner_->states_[1]);
	}

	if (INPUT_MANAGER->GetKey(MK_LBUTTON))
	{
		owner_->ChangeState(owner_->states_[2]);
	}
}

void PlayerIdle::Exit()
{
}

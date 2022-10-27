#include "pch.h"
#include "PlayerWalk.h"
#include "InputManager.h"

PlayerWalk::PlayerWalk(Player* owner)
{
	owner_ = owner;
}

void PlayerWalk::Enter()
{
	owner_->temp_->SetClip("WALK");
}

void PlayerWalk::Update()
{
	if (INPUT_MANAGER->GetKey('A'))
	{
		owner_->Translate(Vector2().Left() * owner_->move_speed_ * DELTA_TIME);
	}

	if (INPUT_MANAGER->GetKey('D'))
	{
		owner_->Translate(Vector2().Right() * owner_->move_speed_ * DELTA_TIME);
	}

	if (INPUT_MANAGER->GetKey('W'))
	{
		owner_->Translate(Vector2().Up() * owner_->move_speed_ * DELTA_TIME);
	}

	if (INPUT_MANAGER->GetKey('S'))
	{
		owner_->Translate(Vector2().Down() * owner_->move_speed_ * DELTA_TIME);
	}

	if (INPUT_MANAGER->GetKeyUp('A') ||
		INPUT_MANAGER->GetKeyUp('D') ||
		INPUT_MANAGER->GetKeyUp('W') ||
		INPUT_MANAGER->GetKeyUp('S'))
	{
		owner_->ChangeState(owner_->states_[0]);
	}

	if (INPUT_MANAGER->GetKey(MK_LBUTTON))
	{
		owner_->ChangeState(owner_->states_[2]);
	}
}

void PlayerWalk::Exit()
{
}

#include "StateMachine.h"

void StateMachine::Start()
{
	current_state_ = GetInitiateState();

	if (current_state_ != nullptr)
	{
		current_state_->Enter();
	}
}

void StateMachine::Update()
{
	if (current_state_ != nullptr)
	{
		current_state_->Update();
	}
}

void StateMachine::ChangeState(State new_state)
{
	if (current_state_ != nullptr)
	{
		current_state_->Exit();
	}

	current_state_ = &new_state;
	current_state_->Enter();
}

State* StateMachine::GetInitiateState()
{
	return nullptr;
}

#include "pch.h"
#include "StateMachine.h"
#include "State.h"

using namespace std;

void StateMachine::Initiate()
{
	current_state_ = GetInitiateState();

	if (current_state_ != nullptr)
	{
		current_state_->Enter();
		OutputDebugString(L"ASDF\n");
	}
}

void StateMachine::Update()
{
	if (current_state_ != nullptr)
	{
		current_state_->Update();
	}
}

std::shared_ptr<State> StateMachine::GetInitiateState()
{
	return nullptr;
}

void StateMachine::ChangeState(shared_ptr<State> state)
{
	if (current_state_ != nullptr)
	{
		current_state_->Exit();
	}

	current_state_ = state;
	current_state_->Enter();
}

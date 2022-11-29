#include "pch.h"
#include "StateMachine.h"
#include "State.h"

using namespace std;

void StateMachine::Initiate()
{
    current_state_ = GetInitiateState();

    if (current_state_ != nullptr)
    {
        current_state_->OnStateEnter();
    }
}

void StateMachine::Update()
{
    if (current_state_ != nullptr)
    {
        current_state_->OnStateUpdate();
    }
}

shared_ptr<State> StateMachine::GetInitiateState()
{
    return nullptr;
}

void StateMachine::ChangeState(shared_ptr<State> state)
{
    if (current_state_ != state)
    {
        if (current_state_ != nullptr)
        {
            current_state_->OnStateExit();
        }

        current_state_ = state;
        current_state_->OnStateEnter();
    }
}

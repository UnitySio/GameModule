#pragma once

#include "State.h"

class StateMachine
{
protected:
	State* current_state_;

	virtual void Start();
	virtual void Update();
	virtual State* GetInitiateState();
public:
	StateMachine() = default;
	~StateMachine() = default;

	void ChangeState(State new_state);
};


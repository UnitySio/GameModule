#pragma once
class State
{
public:
	State() = default;
	~State() = default;

	virtual void Enter();
	virtual void Update();
	virtual void Exit();
};


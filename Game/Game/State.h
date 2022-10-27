#pragma once
class State
{
private:
public:
	State() = default;
	virtual ~State() = default;

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};

#pragma once

class State;

class StateMachine
{
private:
protected:
	std::shared_ptr<State> current_state_;

	virtual void Initiate();
	virtual void Update();

	virtual std::shared_ptr<State> GetInitiateState();
public:
	StateMachine() = default;
	~StateMachine() = default;

	void ChangeState(std::shared_ptr<State> state);
};


#pragma once

#include "State.h"
#include "Boss.h"

class BossDeath :
	public State
{
private:
	Boss* owner_;
public:
	BossDeath(Boss* owner);
	~BossDeath() final = default;

	void OnStateEnter() final;
	void OnStateUpdate() final;
	void OnStateExit() final;
};


#pragma once

#include "State.h"
#include "Boss.h"

class BossIdle :
	public State
{
private:
	Boss* owner_;
public:
	BossIdle(Boss* owner);
	~BossIdle() final = default;

	void OnStateEnter() final;
	void OnStateUpdate() final;
	void OnStateExit() final;
};

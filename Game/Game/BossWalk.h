#pragma once

#include "State.h"
#include "Boss.h"

class BossWalk :
	public State
{
private:
	Boss* owner_;
public:
	BossWalk(Boss* owner);
	~BossWalk() final = default;

	void OnStateEnter() final;
	void OnStateUpdate() final;
	void OnStateExit() final;
};

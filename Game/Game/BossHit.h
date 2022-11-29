#pragma once

#include "State.h"
#include "Boss.h"

class BossHit :
	public State
{
private:
	Boss* owner_;
public:
	BossHit(Boss* owner);
	~BossHit() final = default;

	void OnStateEnter() final;
	void OnStateUpdate() final;
	void OnStateExit() final;
};

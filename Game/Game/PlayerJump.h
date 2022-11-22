#pragma once

#include "State.h"
#include "Player.h"

class PlayerJump :
	public State
{
private:
	Player* owner_;
public:
	PlayerJump(Player* owner);
	~PlayerJump() final = default;

	void OnStateEnter() final;
	void OnStateUpdate() final;
	void OnStateExit() final;
};


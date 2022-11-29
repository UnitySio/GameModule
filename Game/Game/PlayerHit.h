#pragma once

#include "State.h"
#include "Player.h"

class PlayerHit :
	public State
{
private:
	Player* owner_;
public:
	PlayerHit(Player* owner);
	~PlayerHit() final = default;

	void OnStateEnter() final;
	void OnStateUpdate() final;
	void OnStateExit() final;
};


#pragma once

#include "State.h"
#include "Player.h"

class PlayerIdle : public State
{
private:
	Player* owner_;
public:
	PlayerIdle(Player* owner);
	~PlayerIdle() final = default;

	void Enter() final;
	void Update() final;
	void Exit() final;
};

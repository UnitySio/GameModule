#pragma once

#include "State.h"
#include "Player.h"

class PlayerIdle : public State
{
private:
	Player* owner_;
public:
	PlayerIdle(Player* owner);
	~PlayerIdle() override = default;

	void Enter() override;
	void Update() override;
	void Exit() override;
};

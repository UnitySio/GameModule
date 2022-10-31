#pragma once

#include "State.h"
#include "Player.h"

class PlayerJump : public State
{
private:
	Player* owner_;
public:
	PlayerJump(Player* owner);
	~PlayerJump() final = default;

	void Enter() final;
	void Update() final;
	void Exit() final;
};

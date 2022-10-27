#pragma once

#include "State.h"
#include "Player.h"

class PlayerWalk : public State
{
private:
	Player* owner_;
public:
	PlayerWalk(Player* owner);
	~PlayerWalk() override = default;

	void Enter() override;
	void Update() override;
	void Exit() override;
};

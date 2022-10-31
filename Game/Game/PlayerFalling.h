#pragma once

#include "State.h"
#include "Player.h"

class PlayerFalling : public State
{
private:
	Player* owner_;
public:
	PlayerFalling(Player* owner);
	~PlayerFalling() final = default;

	void Enter() final;
	void Update() final;
	void Exit() final;
};

#pragma once

#include "State.h"
#include "Player.h"

class PlayerAttack : public State
{
private:
	Player* owner_;
public:
	PlayerAttack(Player* owner);
	~PlayerAttack() final = default;

	void Enter() final;
	void Update() final;
	void Exit() final;
};

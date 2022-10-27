#pragma once

#include "State.h"
#include "Player.h"

class PlayerAttack : public State
{
private:
	Player* owner_;
public:
	PlayerAttack(Player* owner);
	~PlayerAttack() override = default;

	void Enter() override;
	void Update() override;
	void Exit() override;
};

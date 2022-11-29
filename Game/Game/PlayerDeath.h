#pragma once

#include "State.h"
#include "Player.h"

class PlayerDeath :
	public State
{
private:
    Player* owner_; // 추후 스마트 포인터로 변경 예정
public:
    PlayerDeath(Player* owner);
    ~PlayerDeath() final = default;

    void OnStateEnter() final;
    void OnStateUpdate() final;
    void OnStateExit() final;
};


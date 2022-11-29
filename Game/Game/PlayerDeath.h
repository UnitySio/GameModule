#pragma once

#include "State.h"
#include "Player.h"

class PlayerDeath :
	public State
{
private:
    Player* owner_; // ���� ����Ʈ �����ͷ� ���� ����
public:
    PlayerDeath(Player* owner);
    ~PlayerDeath() final = default;

    void OnStateEnter() final;
    void OnStateUpdate() final;
    void OnStateExit() final;
};


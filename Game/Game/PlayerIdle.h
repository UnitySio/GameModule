#pragma once

#include "State.h"
#include "Player.h"

class PlayerIdle :
    public State
{
private:
    Player* owner_; // 추후 스마트 포인터로 변경 예정
public:
    PlayerIdle(Player* owner);
    ~PlayerIdle() final = default;

    void OnStateEnter() final;
    void OnStateUpdate() final;
    void OnStateExit() final;
};

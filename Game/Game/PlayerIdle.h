#pragma once

#include "State.h"
#include "Player.h"

class PlayerIdle :
    public State
{
private:
    Player* owner_;
public:
    PlayerIdle(Player* owner);
    ~PlayerIdle() final = default;

    void OnStateEnter() final;
    void OnStateUpdate() final;
    void OnStateExit() final;
};

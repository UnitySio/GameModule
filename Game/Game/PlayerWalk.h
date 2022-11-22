#pragma once

#include "State.h"
#include "Player.h"

class PlayerWalk :
    public State
{
private:
    Player* owner_;
public:
    PlayerWalk(Player* owner);
    ~PlayerWalk() final = default;

    void OnStateEnter() final;
    void OnStateUpdate() final;
    void OnStateExit() final;
};

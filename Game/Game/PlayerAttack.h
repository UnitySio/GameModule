﻿#pragma once

#include "State.h"
#include "Player.h"

class PlayerAttack :
    public State
{
private:
    Player* owner_;
    
    std::shared_ptr<Object> hit_box;
public:
    PlayerAttack(Player* owner);
    ~PlayerAttack() final = default;

    void OnStateEnter() final;
    void OnStateUpdate() final;
    void OnStateExit() final;
    void CreateHitBox(); // 추후 함수명 변경 예정
    void DestroyHitBox();
};

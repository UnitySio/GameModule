#pragma once

#include "Object.h"
#include "Player.h"

class PlayerHitBox :
    public Object
{
private:
    Player* owner_;
public:
    PlayerHitBox(Player* owner);
    ~PlayerHitBox() final = default;

    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
};

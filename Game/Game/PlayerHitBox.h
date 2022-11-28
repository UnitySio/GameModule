#pragma once

#include "Object.h"

class PlayerHitBox :
    public Object
{
public:
    PlayerHitBox();
    ~PlayerHitBox() final = default;

    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
};

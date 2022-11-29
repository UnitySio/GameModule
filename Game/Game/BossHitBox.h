#pragma once

#include "Object.h"

class BossHitBox :
	public Object
{
public:
    BossHitBox();
    ~BossHitBox() final = default;

    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
};


#pragma once

#include "Object.h"
#include "Boss.h"

class BossHitBox :
	public Object
{
private:
    Boss* owner_;
public:
    BossHitBox(Boss* owner);
    ~BossHitBox() final = default;

    void Render() final;
    void OnTriggerEnter(Object* other) final;
    void OnTriggerStay(Object* other) final;
    void OnTriggerExit(Object* other) final;
};


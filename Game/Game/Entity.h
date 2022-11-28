#pragma once

class Entity
{
private:
    float hp_;
    float max_hp_;
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void OnDamage(UINT damage);
    virtual void OnDeath() = 0;

    void SetHP(float hp);
    void SetMaxHP(float max_hp);

    float GetHP();
    float GetMaxHP();
};

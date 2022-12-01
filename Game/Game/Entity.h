#pragma once

class Entity
{
private:
    float hp_;
    float max_hp_;

    bool is_death_;
public:
    Entity();
    virtual ~Entity() = default;

    virtual void OnDamage(Vector2 position, UINT damage);
    virtual void OnDeath() = 0;

    void SetHP(float hp);
    void SetMaxHP(float max_hp);

    float GetHP();
    float GetMaxHP();

    bool IsDeath();
};

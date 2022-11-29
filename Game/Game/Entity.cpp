#include "pch.h"
#include "Entity.h"

void Entity::OnDamage(UINT damage)
{
    if (hp_ > 0.f)
    {
        hp_ -= damage;

        if (hp_ <= 0.f)
        {
            OnDeath();
        }
    }
}

void Entity::SetHP(float hp)
{
    hp_ = hp;
}

void Entity::SetMaxHP(float max_hp)
{
    max_hp_ = max_hp;
}

float Entity::GetHP()
{
    return hp_;
}

float Entity::GetMaxHP()
{
    return max_hp_;
}

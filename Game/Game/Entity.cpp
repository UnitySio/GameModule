#include "pch.h"
#include "Entity.h"

Entity::Entity() :
    hp_(),
    max_hp_(),
    is_death_()
{
}

void Entity::OnDamage(UINT damage)
{
    if (hp_ > 0.f)
    {
        hp_ -= damage;

        if (hp_ <= 0.f)
        {
            OnDeath();
            is_death_ = true;
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

bool Entity::IsDeath()
{
    return is_death_;
}

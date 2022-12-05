#include "pch.h"
#include "Entity.h"
#include "SceneManager.h"
#include "Damage.h"

using namespace std;

Entity::Entity() :
    hp_(),
    max_hp_(),
    is_death_()
{
}

void Entity::OnDamage(Vector2 position, UINT damage)
{
    Vector2 final_position = { position.x_, position.y_ - 160.f };
    if (hp_ > 0.f)
    {
        // 추후 최적화를 위해 Object Pool로 변경 예정
        shared_ptr<Object> obj = make_shared<Damage>(damage);
        SCENE->Instantiate(obj, LayerType::kDamage, L"Damage", final_position, {});

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

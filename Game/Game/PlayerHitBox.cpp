#include "pch.h"
#include "PlayerHitBox.h"
#include "BoxCollider2D.h"
#include "Boss.h"

using namespace std;

PlayerHitBox::PlayerHitBox()
{
    AddBoxCollider2D();
    GetBoxCollider2D()->SetSize({ 120.f, 120.f });
}

void PlayerHitBox::Render()
{
    Object::Render();
}

void PlayerHitBox::OnTriggerEnter(Object* other)
{
    (*(Boss*)other).OnDamage(1000);
}

void PlayerHitBox::OnTriggerStay(Object* other)
{
}

void PlayerHitBox::OnTriggerExit(Object* other)
{
}
